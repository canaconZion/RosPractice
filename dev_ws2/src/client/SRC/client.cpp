// client.cpp
#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"                                    
#include "../include/client.h"

#include <chrono>
#include <cstdlib>
#include <memory>
#include<vector>
using namespace std;

using namespace std::chrono_literals;

 // Constructor 
ClientHandler::ClientHandler(){

}

 // Destructor
ClientHandler::~ClientHandler(){
  
}


 // Normal function - send parameters
bool ClientHandler::sendParams(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 3) {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "缺少必须参数");      
      return false;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_client");  
  rclcpp::Client<tutorial_interfaces::srv::AddThreeInts>::SharedPtr client =               
    node->create_client<tutorial_interfaces::srv::AddThreeInts>("add_three_ints");         

  auto request = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();      
  request->lat = atoll(argv[1]);
  request->lng = atoll(argv[2]);
  if (-90 <= request->lat <= 90 || -180 <= request->lat<= 180){
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "输入经纬度有误");      
      return false;
  }                                                         

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return false;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "distance: %ld km", result.get()->distance);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service distance");
  }

  rclcpp::shutdown();
  return true;
}
