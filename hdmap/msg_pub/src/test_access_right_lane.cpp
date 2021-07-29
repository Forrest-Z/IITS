#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "fead_interfaces/srv/access_lane_id.hpp"
#include "fead_interfaces/srv/access_left_lane.hpp"
#include "fead_interfaces/srv/access_right_lane.hpp"
#include "fead_interfaces/srv/routing.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;
using std::placeholders::_1;

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  if (argc != 4) {  // CHANGE
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                "usage: three axis: X Y Z");  // CHANGE
    return 1;
  }

  std::shared_ptr<rclcpp::Node> node =
      rclcpp::Node::make_shared("AccessRightLane_client");  // CHANGE
  rclcpp::Client<fead_interfaces::srv::AccessRightLane>::SharedPtr
      client =  // CHANGE
      node->create_client<fead_interfaces::srv::AccessRightLane>(
          "AccessRightLane");  // CHANGE

  auto request = std::make_shared<
      fead_interfaces::srv::AccessRightLane::Request>();  // CHANGE
  request->waypoint.x = atof(argv[1]);                    // CHANGE
  request->waypoint.y = atof(argv[2]);                    // CHANGE
  request->waypoint.z = atof(argv[3]);                    // CHANGE

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),
                   "Interrupted while waiting for the service. Exiting.");
      return 0;
    }

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
      rclcpp::executor::FutureReturnCode::SUCCESS) {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Flag: %ld", result.get()->flag);
    if (result.get()->flag) {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                  "Right Waypoint: %.4f %.4f %.4f", result.get()->waypoint.x,
                  result.get()->waypoint.y, result.get()->waypoint.z);
    }

  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),
                 "Failed to call access_lane_id");  // CHANGE
  }

  rclcpp::shutdown();
  return 0;
}