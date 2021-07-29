#include <stddef.h>
#include <stdio.h>  // This ert_main.c example uses printf/fflush

#include <chrono>
#include <iostream>
#include <memory>

#include "CNHTC_VEHICLE_MODEL_PureSL.h"  // Model's header file
#include "fead_interfaces/msg/vehicle_model_input.hpp"
#include "fead_interfaces/msg/vehicle_model_output.hpp"
#include "fead_interfaces/srv/control.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rtwtypes.h"
#include "std_msgs/msg/string.hpp"
#include "zero_crossing_types.h"

using namespace std::chrono_literals;
using std::placeholders::_1;

static CNHTC_VEHICLE_MODEL_PureSLModelClass
    CNHTC_VEHICLE_MODEL_PureSL_Obj;  // Instance of model class

real_T pedalPos_pct;         // '<Root>/pedalPos_pct'
real_T XBR1_ExternalAccele;  // '<Root>/XBR1_ExternalAccele'
real_T SteerWhAngle_rad;     // '<Root>/SteerWhAngle_rad'
real_T Grade_deg;            // '<Root>/Grade_deg'
real_T XBR1_Ctrl_Mode;       // '<Root>/XBR1_Ctrl_Mode'

//
// Associating rt_OneStep with a real-time clock or interrupt service routine
// is what makes the generated code "real-time".  The function rt_OneStep is
// always associated with the base rate of the model.  Subrates are managed
// by the base rate from inside the generated code.  Enabling/disabling
// interrupts and floating point context switches are target specific.  This
// example code indicates where these should take place relative to executing
// the generated code step function.  Overrun behavior should be tailored to
// your application needs.  This example simply sets an error status in the
// real-time model and returns from rt_OneStep.
//
ExtY_CNHTC_VEHICLE_MODEL_PureSL_T rt_OneStep(void);
ExtY_CNHTC_VEHICLE_MODEL_PureSL_T rt_OneStep(void) {
  static boolean_T OverrunFlag = false;

  ExtY_CNHTC_VEHICLE_MODEL_PureSL_T output;

  // Disable interrupts here

  // Check for overrun
  // if (OverrunFlag) {
  //   rtmSetErrorStatus(CNHTC_VEHICLE_MODEL_PureSL_Obj.getRTM(), "Overrun");
  //   return;
  // }

  OverrunFlag = true;

  // Save FPU context here (if necessary)
  // Re-enable timer or interrupt here
  // Set model inputs here

  // Step the model for base rate
  output = CNHTC_VEHICLE_MODEL_PureSL_Obj.step();

  // Get model outputs here

  // Indicate task complete
  OverrunFlag = false;

  // Disable interrupts here
  // Restore FPU context here (if necessary)
  // Enable interrupts here
  return output;
}

inline real_T speed_kmh_to_ms(real_T speed) { return speed / 3.6; }

void run_one_step(
    const std::shared_ptr<fead_interfaces::srv::Control::Request> request,
    std::shared_ptr<fead_interfaces::srv::Control::Response> response) {
  // 3d simulator
  pedalPos_pct = request->input.throttle;
  XBR1_ExternalAccele = request->input.brake;
  SteerWhAngle_rad = request->input.steer;
  XBR1_Ctrl_Mode = request->input.ctrlmode;
  Grade_deg = 0;  // grade

  /***************************************/
  // ert_output_data sim_output;
  // for (int i = 0; i < 10; i++) {
  //   sim_output = ert_run_one_step(sim_input);
  // }
  auto output = rt_OneStep();
  /***************************************/

  response->output.control_frame_id = request->input.control_frame_id;
  response->output.vx = speed_kmh_to_ms(output.Vx_kph);
  response->output.vy = speed_kmh_to_ms(output.Vy_kph);
  response->output.xo = output.X;
  response->output.yo = output.Y;
  response->output.zo = output.Z;
  response->output.eng_trq_nm = output.EngTrq_Nm;
  response->output.eng_spd_rpm = output.EngSpd_rpm;
  response->output.gear_pos = output.GearPos;
  response->output.yaw = output.Yaw_deg;
  response->output.ax = output.ax_mps2;
  response->output.ay = 0;
  response->output.av_z = 0;
  // send back input for easy access
  response->output.input = request->input;

  // RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%d]",
  // response->output.control_frame_id);
}

class SimuLinkBridgeNode : public rclcpp::Node {
 public:
  SimuLinkBridgeNode() : Node("simulink_bridge"), count_(0) {
    num = 1;
    // Initialize model
    CNHTC_VEHICLE_MODEL_PureSL_Obj.initialize();

    // create topics
    publisher_ =
        this->create_publisher<fead_interfaces::msg::VehicleModelOutput>(
            "VehicleModelOutput", 10);

    // timer_ = this->create_wall_timer(
    //  500ms, std::bind(&TruckSimBridgeNode::timer_callback, this));

    // subscription_ =
    //     this->create_subscription<fead_interfaces::msg::VehicleModelInput>(
    //         "VehicleModelInput", 10,
    //         std::bind(&SimuLinkBridgeNode::recv_sim_data_callback, this,
    //         _1));
    control_service = this->create_service<fead_interfaces::srv::Control>(
        "Control", &run_one_step);
  }

 private:
  // void timer_callback()
  // {
  //   //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'",
  //   message.data.c_str());

  //   auto input_msg = fead_interfaces::msg::VehicleModelInput();
  //   input_msg.throttle = 50;

  //   recv_sim_data_callback(fead_interfaces::msg::VehicleModelInput::SharedPtr(&input_msg));
  // }

  void recv_sim_data_callback(
      const fead_interfaces::msg::VehicleModelInput::SharedPtr msg) {
    // RCLCPP_INFO(this->get_logger(), "recv input: '%f'", msg->throttle);
    auto message = fead_interfaces::msg::VehicleModelOutput();

    pedalPos_pct = msg->throttle;
    SteerWhAngle_rad = msg->steer;
    Grade_deg = msg->grade_deg;
    XBR1_ExternalAccele = msg->brake;
    if (msg->brake > 0.0) {
      XBR1_Ctrl_Mode = 1;
    } else {
      XBR1_Ctrl_Mode = 0;
    }

    auto output = rt_OneStep();

    message.gear_pos = output.GearPos;
    message.eng_trq_nm = output.EngTrq_Nm;
    message.eng_spd_rpm = output.EngSpd_rpm;
    message.engine_torque_loss_percent = output.engine_torque_loss_percent;
    message.engine_torque_percent = output.engine_torque_percent;

    message.yaw = output.Yaw_deg;

    message.xo = output.X;
    message.yo = output.Y;
    message.zo = output.Z;

    message.vx = output.Vx_kph;
    message.vy = output.Vy_kph;
    // message.vz = output.Vz_kph;

    publisher_->publish(message);
  }

  rclcpp::Subscription<fead_interfaces::msg::VehicleModelInput>::SharedPtr
      subscription_;
  rclcpp::Publisher<fead_interfaces::msg::VehicleModelOutput>::SharedPtr
      publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Service<fead_interfaces::srv::Control>::SharedPtr control_service;

  size_t count_;
  int num;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimuLinkBridgeNode>());
  rclcpp::shutdown();
  return 0;
}