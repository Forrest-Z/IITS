
#include <chrono>
#include <cstdlib>
#include <functional>
#include <memory>
#include <string>

#include "fead_interfaces/srv/get_nearest_center_polyline_point2d.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared(
      "GetNearestCenterPolylinePoint2d_client");  // CHANGE
  rclcpp::Client<fead_interfaces::srv::GetNearestCenterPolylinePoint2d>::
      SharedPtr client =  // CHANGE
      node->create_client<
          fead_interfaces::srv::GetNearestCenterPolylinePoint2d>(
          "GetNearestCenterPolylinePoint2d");  // CHANGE

  auto request = std::make_shared<
      fead_interfaces::srv::GetNearestCenterPolylinePoint2d::Request>();
  // request->lane_id.data = "1660148";
  request->lane_id.data = "0";
  request->point.x = -308.181;
  request->point.y = -353.725;

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
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "point: %.4f, %.4f, %.4f",
                result.get()->center_polyline_point.pt.x,
                result.get()->center_polyline_point.pt.y,
                result.get()->center_polyline_point.pt.z);
  } else {
    RCLCPP_ERROR(
        rclcpp::get_logger("rclcpp"),
        "Failed to call get_nearest_center_polyline_point2d");  // CHANGE
  }

  rclcpp::shutdown();
  return 0;
}