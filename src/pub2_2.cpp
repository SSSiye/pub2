//2101069 이시예
//************************************************
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include <memory>
#include <iostream>
#include <functional>

using namespace std::chrono_literals;

void callback(
    rclcpp::Node::SharedPtr node, 
    rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr pub)
{
    // 실수값 3개를 입력받아 Vector3 메시지로 퍼블리시
    float x, y, z;
    std::cout << "Enter x value: ";
    std::cin >> x;
    std::cout << "Enter y value: ";
    std::cin >> y;
    std::cout << "Enter z value: ";
    std::cin >> z;

    auto message = geometry_msgs::msg::Vector3();
    message.x = x;
    message.y = y;
    message.z = z;

    RCLCPP_INFO(node->get_logger(), "Publishing: x=%f, y=%f, z=%f", message.x, message.y, message.z);
    pub->publish(message);  // 퍼블리시
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);  // ROS2 초기화
    auto node = std::make_shared<rclcpp::Node>("pub2_2_node");  // 노드 이름을 "pub2_2_node"로 설정
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));  // QoS 설정
    auto pub = node->create_publisher<geometry_msgs::msg::Vector3>("mytopic", qos_profile);  // Vector3 타입으로 퍼블리셔 생성
    std::function<void()> fn = std::bind(callback, node, pub);  // callback 함수와 퍼블리셔를 바인딩
    auto timer = node->create_wall_timer(100ms, fn);  // 100ms마다 콜백 함수 실행
    rclcpp::spin(node);  // 노드 실행
    rclcpp::shutdown();  // 종료
    return 0;
}
