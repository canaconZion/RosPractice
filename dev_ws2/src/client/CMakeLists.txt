cmake_minimum_required(VERSION 3.8)
project(client)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tutorial_interfaces REQUIRED)

set(SRC
  SRC/client.cpp
  SRC/main.cpp
)

add_executable(client 
              ${SRC}
              )
ament_target_dependencies(client
  rclcpp tutorial_interfaces)

# 5. Add the header file in the current project pay attention to the order requirements, can not be chaotic
target_include_directories(client
    PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
)

 # If it is a test code
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
     # 入 加 test package
  find_package(ament_cmake_gtest REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  # set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  # set(ament_cmake_cpplint_FOUND TRUE)
  set(TEST
      Test/main.cpp
      Test/clientTest.cpp
    )
     # Generate the TEST execution file to join the GTEST. $ {Project_name} _test is a custom TEST execution file name; test / demo_test.cpp is TEST source path
     # Note that when the packet is packed, it is no longer needed to import .h files, because we have imported it in the client.cpp .h file
     # In addition, note that Main.cpp in the development code cannot be imported, because there is already a test of main.cpp
  ament_add_gtest(${PROJECT_NAME}_test ${TEST} SRC/client.cpp)
     # 必 注意 依 依 依 依 依 包 包
  ament_target_dependencies(${PROJECT_NAME}_test rclcpp tutorial_interfaces)

  install(TARGETS
          ${PROJECT_NAME}_test
                     # Install the generated TEST execution file to the path after Destination
          DESTINATION lib/${PROJECT_NAME})                                       
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
  client
  DESTINATION lib/${PROJECT_NAME})

 # Set the compilation build type as debug mode
set(CMAKE_BUILD_TYPE Debug)   
 # 成能 覆 文件 文件
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")

ament_package()