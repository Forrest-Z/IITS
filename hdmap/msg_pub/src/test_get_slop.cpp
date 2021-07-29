#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "fead_interfaces/srv/access_lane_id.hpp"
#include "fead_interfaces/srv/access_left_lane.hpp"
#include "fead_interfaces/srv/access_right_lane.hpp"
#include "fead_interfaces/srv/get_slop.hpp"
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
      rclcpp::Node::make_shared("GetSlop_client");  // CHANGE
  rclcpp::Client<fead_interfaces::srv::GetSlop>::SharedPtr client =
      node->create_client<fead_interfaces::srv::GetSlop>("GetSlop");  // CHANGE

  auto request =
      std::make_shared<fead_interfaces::srv::GetSlop::Request>();  // CHANGE
  request->pos.x = atof(argv[1]);                                  // CHANGE
  request->pos.y = atof(argv[2]);
  request->pos.z = atof(argv[3]);

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
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Slop: %.4f", result.get()->slop);

  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),
                 "Failed to call get_slop");  // CHANGE
  }

  rclcpp::shutdown();
  return 0;
}