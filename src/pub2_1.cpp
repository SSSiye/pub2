//2101069 이시예
//************************************************
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include <memory>
#include <chrono>
#include <functional>

using namespace std::chrono_literals;

void callback(
    rclcpp::Node::SharedPtr node, 
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub)
{
    static int count = 0;  // 0으로 초기화된 정수값
    auto message = std_msgs::msg::Int32();
    message.data = count++;  // count 값이 1씩 증가
    RCLCPP_INFO(node->get_logger(), "Publish: %d", message.data);  // 정수값을 로그로 출력
    pub->publish(message);  // 퍼블리시
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);  // ROS2 초기화
    auto node = std::make_shared<rclcpp::Node>("pub2_1_node");  // 노드 이름을 "pub2_1_node"로 설정
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));  // QoS 설정
    auto pub = node->create_publisher<std_msgs::msg::Int32>("mytopic", qos_profile);  // Int32 타입으로 퍼블리셔 생성
    std::function<void()> fn = std::bind(callback, node, pub);  // callback 함수와 퍼블리셔를 바인딩
    auto timer = node->create_wall_timer(100ms, fn);  // 100ms마다 콜백 함수 실행
    rclcpp::spin(node);  // 노드 실행
    rclcpp::shutdown();  // 종료
    return 0;
}
