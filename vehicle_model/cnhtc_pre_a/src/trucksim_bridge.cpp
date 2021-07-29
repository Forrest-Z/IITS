//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: trucksim_bridge.cpp
//

#include <math.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "ert_api.h"
#include "fead_interfaces/msg/vehicle_model_input.hpp"
#include "fead_interfaces/msg/vehicle_model_output.hpp"
#include "fead_interfaces/srv/control.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using namespace std;

inline real_T speed_kmh_to_ms(real_T speed) { return speed / 3.6; }

void run_one_step(
    const std::shared_ptr<fead_interfaces::srv::Control::Request> request,
    std::shared_ptr<fead_interfaces::srv::Control::Response> response) {
  ert_input_data sim_input;
  sim_input.pedalPos_pct = request->input.throttle;
  sim_input.XBR1_ExternalAccele = request->input.brake;
  sim_input.XBR1_Ctrl_Mode = request->input.ctrlmode;
  sim_input.SteerWhAngle_rad = request->input.steer;

  /***************************************/
  ert_output_data sim_output;
  for (int i = 0; i < 10; i++) {
    sim_output = ert_run_one_step(sim_input);
  }
  /***************************************/

  response->output.control_frame_id = request->input.control_frame_id;
  response->output.vx = speed_kmh_to_ms(sim_output.trucksim.Vx);
  response->output.vy = speed_kmh_to_ms(sim_output.trucksim.Vy);
  response->output.vz = speed_kmh_to_ms(sim_output.trucksim.Vz);
  response->output.xo = sim_output.trucksim.Xo;
  response->output.yo = sim_output.trucksim.Yo;
  response->output.zo = sim_output.trucksim.Zo;
  response->output.eng_trq_nm = sim_output.simulink._EngTrq_Nm;
  response->output.eng_spd_rpm = sim_output.simulink._EngSpd_rpm;
  response->output.engine_torque_percent =
      sim_output.simulink._engine_torque_percent;
  response->output.engine_torque_loss_percent =
      sim_output.simulink._engine_torque_loss_percent;
  response->output.gear_pos = sim_output.simulink._GearPos;
  response->output.yaw = sim_output.trucksim.Yaw;
  response->output.pitch = sim_output.trucksim.Pitch;
  response->output.roll = sim_output.trucksim.Roll;
  response->output.ax = sim_output.trucksim.Ax;
  response->output.ay = sim_output.trucksim.Ay;
  response->output.t_stamp = sim_output.trucksim.T_Stamp;
  response->output.av_z = sim_output.trucksim.AVz;
  response->output.total_fuel = sim_output.simulink.fuel_consumption;
  response->output.shift_in_process = sim_output.simulink._shift_in_process;
  response->output.brake_pressure_front_left_kpa =
      sim_output.simulink._fwdWhlPre_Mpa[0];
  response->output.brake_pressure_front_right_kpa =
      sim_output.simulink._fwdWhlPre_Mpa[1];
  response->output.brake_pressure_rear_left_kpa =
      sim_output.simulink._bwdWhlPre_Mpa[0];
  response->output.brake_pressure_rear_right_kpa =
      sim_output.simulink._bwdWhlPre_Mpa[1];
  response->output.brake_pressure_trailer_command_kpa =
      sim_output.simulink._TrailWhlPre_Mpa[0];
  // send back input for easy access
  response->output.input = request->input;

  //   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "--------vz: [%f]",
  //               sim_output.trucksim.Vz);
}

class TruckSimBridgeNode : public rclcpp::Node {
 public:
  TruckSimBridgeNode() : Node("trucksim_bridge_trailer") {
    this->declare_parameter<std::string>(
        "sim_file_path", "resource/simfile_cnhtc_pre_a_jinan.sim");
    this->get_parameter("sim_file_path", sim_file_path);

    ert_init(true, sim_file_path.c_str());
    // ert_init(false); // without trucksim

    control_service = this->create_service<fead_interfaces::srv::Control>(
        "Control", &run_one_step);
  }

  std::string sim_file_path;
  rclcpp::Service<fead_interfaces::srv::Control>::SharedPtr control_service;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TruckSimBridgeNode>());
  rclcpp::shutdown();
  return 0;
}
