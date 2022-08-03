#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"                                        // CHANGE
#include <iostream>
#include <memory>

const float EARTH_RADIUS = 6371000;

// 大地坐标系资料WGS-84,长半径 6378137
const float WGS84_L_RADIUS = 6378137;

// 大地坐标系资料WGS-84,短半径 6356752.3142 */
const float WGS84_S_RADIUS = 6356752.3142;

// 扁率
const float M_F = 1 / 298.2572236;

// 角度转弧度
float A2R(float d) { return d * M_PI / 180.0; }

// 弧度转角度
float R2A(float d) { return d / M_PI * 180.0; }

// 1、计算两个经纬度之间的距离(m)
float GetDistanceCpp(float lat1, float lng1, float lat2, float lng2)
{
    float radLat1 = A2R(lat1);
    float radLat2 = A2R(lat2);
    float a = radLat1 - radLat2;
    float b = A2R(lng1) - A2R(lng2);
    float s = 2 * asin(sqrt(pow(sin(a/2),2) +cos(radLat1)*cos(radLat2)*pow(sin(b/2),2)));
    s = s * EARTH_RADIUS;
    return s;
}

void add(const std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Request> request,     // CHANGE
          std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Response>       response)  // CHANGE
{
  response->distance=GetDistanceCpp(request->lat,request->lng,22.55,114.05)/1000.0;
  //response->sum = request->a + request->b + request->c;                                      // CHANGE
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\nlatitude: %ld" " longitude: %ld" ,  // CHANGE
                request->lat, request->lng);                                         // CHANGE
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld] km", (long int)response->distance);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_server");   // CHANGE

  rclcpp::Service<tutorial_interfaces::srv::AddThreeInts>::SharedPtr service =               // CHANGE
    node->create_service<tutorial_interfaces::srv::AddThreeInts>("add_three_ints",  &add);   // CHANGE

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add three ints.");                     // CHANGE

  rclcpp::spin(node);
  rclcpp::shutdown();
}

