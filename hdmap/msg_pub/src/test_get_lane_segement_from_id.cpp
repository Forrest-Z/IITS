#include <chrono>
#include <cstdlib>
#include <functional>
#include <memory>
#include <string>

#include "fead_interfaces/srv/get_lane_segment_from_id.hpp"
#include "gtest/gtest.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

std::shared_ptr<rclcpp::Node> node;  // CHANGE
rclcpp::Client<fead_interfaces::srv::GetLaneSegmentFromID>::SharedPtr
    client;  // CHANGE

TEST(GetLaneSegmentFromID, test1) {
  auto request =
      std::make_shared<fead_interfaces::srv::GetLaneSegmentFromID::Request>();
  request->id.data = "1650148";

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),
                   "Interrupted while waiting for the service. Exiting.");
      return;
    }

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  rclcpp::spin_until_future_complete(node, result);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Lane ID: %s, type: %d",
              result.get()->lane_segment.id.data.c_str(),
              result.get()->lane_segment.type);
  EXPECT_EQ(2, result.get()->lane_segment.type);
  // EXPECT_EQ(0, result.get()->lane_segment.lane_turn);
}

TEST(GetLaneSegmentFromID, test2) {
  auto request =
      std::make_shared<fead_interfaces::srv::GetLaneSegmentFromID::Request>();
  request->id.data = "2";

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),
                   "Interrupted while waiting for the service. Exiting.");
      return;
    }

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  rclcpp::spin_until_future_complete(node, result);
  EXPECT_EQ(0, result.get()->lane_segment.type);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("GetLaneSegmentFromID_client");  // CHANGE

  client =  // CHANGE
      node->create_client<fead_interfaces::srv::GetLaneSegmentFromID>(
          "GetLaneSegmentFromID");  // CHANGE
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  rclcpp::shutdown();
  return 0;
}