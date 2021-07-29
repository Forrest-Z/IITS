//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: simulink_bridge.cpp
//

#include <chrono>
#include <memory>

#include <stddef.h>
#include <stdio.h>                // This ert_main.c example uses printf/fflush
#include <iostream>
#include "CNHTC_VEHICLE_MODEL_PureSL.h" // Model's header file
#include "rtwtypes.h"
#include "zero_crossing_types.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "fead_interfaces/msg/vehicle_model_input.hpp"
#include "fead_interfaces/msg/vehicle_model_output.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

static CNHTC_VEHICLE_MODEL_PureSLModelClass CNHTC_VEHICLE_MODEL_PureSL_Obj; // Instance of model class

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

void rt_OneStep(void)
  {
    static boolean_T OverrunFlag = false;

    // Disable interrupts here

    // Check for overrun
    if (OverrunFlag) {
        rtmSetErrorStatus(CNHTC_VEHICLE_MODEL_PureSL_Obj.getRTM(), "Overrun");
        return;
    }

    OverrunFlag = true;

    // Save FPU context here (if necessary)
    // Re-enable timer or interrupt here
    // Set model inputs here

    // Step the model for base rate
    CNHTC_VEHICLE_MODEL_PureSL_Obj.step();

    // Get model outputs here

    // Indicate task complete
    OverrunFlag = false;

    // Disable interrupts here
    // Restore FPU context here (if necessary)
    // Enable interrupts here
}

class SimuLinkBridgeNode : public rclcpp::Node
{
public:
  SimuLinkBridgeNode()
  : Node("simulink_bridge"), count_(0)
  {
    num = 1;
    //Initialize model
    CNHTC_VEHICLE_MODEL_PureSL_Obj.initialize();

    //create topics
    publisher_ = this->create_publisher<fead_interfaces::msg::VehicleModelOutput>("SimuLinkOutput", 10);
    
    //timer_ = this->create_wall_timer(
    //  500ms, std::bind(&TruckSimBridgeNode::timer_callback, this));
    
    subscription_ = this->create_subscription<fead_interfaces::msg::VehicleModelInput>(
        "SimuLinkInput", 10, std::bind(&SimuLinkBridgeNode::recv_sim_data_callback, this, _1));
  }

private:

  void timer_callback()
  {
    //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());

    auto input_msg = fead_interfaces::msg::VehicleModelInput();
    input_msg.throttle = 50;

    recv_sim_data_callback(fead_interfaces::msg::VehicleModelInput::SharedPtr(&input_msg));
  }

  void recv_sim_data_callback(const fead_interfaces::msg::VehicleModelInput::SharedPtr msg)
  {
      //RCLCPP_INFO(this->get_logger(), "recv input: '%f'", msg->throttle);

      auto message = fead_interfaces::msg::VehicleModelOutput();
      
      pedalPos_pct = msg->throttle;                   
      XBR1_ExternalAccele = msg->brake;            
      SteerWhAngle_rad = msg->steer;               
      Grade_deg = msg->grade_deg;
      if(msg->brake>0)                      
        XBR1_Ctrl_Mode = 1;                 
      
      rt_OneStep();

      ++num;

      message.gear_pos = CNHTC_VEHICLE_MODEL_PureSL_Obj.CNHTC_VEHICLE_MODEL_PureSL_Y.GearPos;                 
      message.eng_trq_nm = CNHTC_VEHICLE_MODEL_PureSL_Obj.CNHTC_VEHICLE_MODEL_PureSL_Y.EngTrq_Nm;              
      message.eng_spd_rpm = CNHTC_VEHICLE_MODEL_PureSL_Obj.CNHTC_VEHICLE_MODEL_PureSL_Y.EngSpd_rpm;                 
      message.engine_torque_loss_percent = CNHTC_VEHICLE_MODEL_PureSL_Obj.CNHTC_VEHICLE_MODEL_PureSL_Y.engine_torque_loss_percent;  
      message.engine_torque_percent = CNHTC_VEHICLE_MODEL_PureSL_Obj.CNHTC_VEHICLE_MODEL_PureSL_Y.engine_torque_percent;      
      message.vx= CNHTC_VEHICLE_MODEL_PureSL_Obj.CNHTC_VEHICLE_MODEL_PureSL_Y.Velong_kph_p;            
      message.yaw = CNHTC_VEHICLE_MODEL_PureSL_Obj.CNHTC_VEHICLE_MODEL_PureSL_Y.Yaw_deg_n;                 
      message.ax = CNHTC_VEHICLE_MODEL_PureSL_Obj.CNHTC_VEHICLE_MODEL_PureSL_Y.ax_mps2_f;                   
      message.vx_kph_e = CNHTC_VEHICLE_MODEL_PureSL_Obj.CNHTC_VEHICLE_MODEL_PureSL_Y.Vx_kph_e;                 
      message.vy_kph_a = CNHTC_VEHICLE_MODEL_PureSL_Obj.CNHTC_VEHICLE_MODEL_PureSL_Y.Vy_kph_a;                   
      message.xo = CNHTC_VEHICLE_MODEL_PureSL_Obj.CNHTC_VEHICLE_MODEL_PureSL_Y.X_p;                   
      message.yo = CNHTC_VEHICLE_MODEL_PureSL_Obj.CNHTC_VEHICLE_MODEL_PureSL_Y.Y_h;
     

      // //message.xo_2 = sim_output.trucksim.Xo_2;
      publisher_->publish(message);
      std::cout<<num<<" "<<message.vx<<std::endl;
  }

  rclcpp::Subscription<fead_interfaces::msg::VehicleModelInput>::SharedPtr subscription_;
  rclcpp::Publisher<fead_interfaces::msg::VehicleModelOutput>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  
  size_t count_;
  int num;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimuLinkBridgeNode>());
  rclcpp::shutdown();
  return 0;
}