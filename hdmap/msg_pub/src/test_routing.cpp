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

  if (argc != 7) {  // CHANGE
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                "usage: three axis: X1 Y1 Z1 X2 Y2 Z2");  // CHANGE
    return 1;
  }

  std::shared_ptr<rclcpp::Node> node =
      rclcpp::Node::make_shared("Routing_client");                    // CHANGE
  rclcpp::Client<fead_interfaces::srv::Routing>::SharedPtr client =   // CHANGE
      node->create_client<fead_interfaces::srv::Routing>("Routing");  // CHANGE

  auto request =
      std::make_shared<fead_interfaces::srv::Routing::Request>();  // CHANGE
  request->begin_pos.x = atof(argv[1]);                            // CHANGE
  request->begin_pos.y = atof(argv[2]);                            // CHANGE
  request->begin_pos.z = atof(argv[3]);                            // CHANGE
  request->end_pos.x = atof(argv[4]);                              // CHANGE
  request->end_pos.y = atof(argv[5]);                              // CHANGE
  request->end_pos.z = atof(argv[6]);                              // CHANGE

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
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Lane ID: %ld",
                result.get()->lane_id[0]);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),
                 "Failed to call access_lane_id");  // CHANGE
  }

  rclcpp::shutdown();
  return 0;
}