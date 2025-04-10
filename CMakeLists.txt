cmake_minimum_required(VERSION 3.5)
project(pub2)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

#build
add_executable(pub2 src/pub.cpp)
ament_target_dependencies(pub2 rclcpp std_msgs)

add_executable(pub2_1 src/pub2_1.cpp)
ament_target_dependencies(pub2_1 rclcpp std_msgs)

add_executable(pub2_2 src/pub2_2.cpp)
ament_target_dependencies(pub2_2 rclcpp geometry_msgs)

# Install
install(TARGETS
  pub2
  pub2_1
  pub2_2
  DESTINATION lib/${PROJECT_NAME})

ament_package()