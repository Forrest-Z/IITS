#
# Copyright (c) 2020 Inceptio Corporation.
#
# This work is licensed under the terms of the MIT license.
# For a copy, see <https://opensource.org/licenses/MIT>.
#

std_msgs/Header header

#Both
float32 gear_pos                       #float32 gearpos                     
float32 eng_trq_nm                    #float32 engtrq_nm               
float32 eng_spd_rpm                   #float32 engspd_rpm                 
float32 engine_torque_loss_percent    #float32 engine_torque_loss_percent        
float32 engine_torque_percent         #float32 engine_torque_percent           

#uint8 foundation_brake_in_use
uint8 shift_in_process
float32 brake_pressure_front_left_kpa
float32 brake_pressure_front_right_kpa
float32 brake_pressure_rear_left_kpa
float32 brake_pressure_rear_right_kpa
float32 brake_pressure_trailer_command_kpa

float32 vx      #float32 velong_kph_p            
float32 yaw     #float32 yaw_deg_n                                 
float32 ax　　　　#float32 ax_mps2_f                                      
float32 xo       #float32 x_p                    
float32 yo       #float32 y_h 
float32 zo 

#float32 omega_w_rads  #tire_rads

#simulink(world coordination)
float32 vx_kph_e                  
float32 vy_kph_a 

#trucksim
float32 trans_tor_out_nm            #/* '<S1>/DriveLine' 变速箱输出轴扭矩*/
float32 steer_wh_angle_dz_deg         #/* '<Root>/SteerWhlMdl' ，方向盘转角*/
float32 throttle_pct                #/* '<Root>/Gain' 油门开度百分比*/

float32 av_z
float32 av_z_2
float32 vy
float32 vz
float32 ay
float32 xo_2
float32 yo_2
float32 steer_l1
float32 steer_r1
float32 yaw_2
float32 art_h
float32 pitch
float32 pitch_2
float32 roll
float32 roll_2
float32 station
float32 t_stamp

# for control & vehicle model
int64 control_frame_id

# calculated metrics 
float32 total_fuel 
float32 fuel_rate
float32 comprehensive_metric

# corresponding input 
VehicleModelInput input