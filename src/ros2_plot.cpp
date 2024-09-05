#include <cstdio>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include "ros2_plot/shared_data.hpp"
#include <signal.h>

void sigintHandler(int sig) {
  (void) sig;
  // 执行特定的中断处理操作
  // 例如，关闭打开的文件、释放资源等
  // 然后退出程序
  rclcpp::shutdown();
  exit(0);
}

int main(int argc, char ** argv) {
  rclcpp::init(argc, argv);
  signal(SIGINT, sigintHandler);

  rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("ros2_plot");
  auto advertiser = node->create_publisher<std_msgs::msg::Float64MultiArray>("/shared_data", 1);
  
  SharedMemoryObject<SharedData> shared_memory;
  shared_memory.CreateNew(SHARED_MEMORY_NAME);
  shared_memory.Init(true);
  shared_memory.SimulatorIsDone();

  auto subscriber = node->create_subscription<std_msgs::msg::Float64MultiArray>("/shared_data_set", 1, [&](const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    RCLCPP_INFO(node->get_logger(), "receive data size :'%ld'", msg->data.size());
    for (size_t i = 0; i < msg->data.size(); i++) {
      shared_memory().ros2sim.data[i] = msg->data[i];
    }
  });

  std_msgs::msg::Float64MultiArray msg;
  msg.data.resize(120);

  while(!shared_memory.TryWaitForRobot()) {
    rclcpp::sleep_for(std::chrono::milliseconds(3));
  }

  RCLCPP_INFO(node->get_logger(), "Start publishing data");

  while (rclcpp::ok()) {
    if(shared_memory.WaitForRobotWithTimeout()) {
      for (size_t i = 0; i < 120; i++) {
        msg.data[i] = shared_memory().sim2ros.data[i];
      }
      advertiser->publish(msg);
    }
    rclcpp::spin_some(node);
    // rclcpp::sleep_for(std::chrono::milliseconds(1));
  }

  rclcpp::shutdown();
  return 0;
}
