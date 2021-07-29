#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
"""
Class that handle communication between CARLA and ROS
"""
import queue

import sys
from distutils.version import LooseVersion
from threading import Thread, Lock, Event
import pkg_resources

import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Header

from fead_interfaces.msg import SimTick
from fead_interfaces.msg import VehicleModelOutput
from fead_interfaces.msg import LaneChangeMsgs
from fead_interfaces.msg import VehicleModelReset

#import carla

class ScenarioJinan(Node):

    def __init__(self):
        super().__init__('scenario_jinan')

        self.subscription_vehiclemodel = self.create_subscription(
            VehicleModelOutput,
            'VehicleModelOutput',
            self.vehicle_output_callback,
            10)
        self.subscription_vehiclemodel  # prevent unused variable warning

        self.subscription_lanchange = self.create_subscription(
            LaneChangeMsgs,
            'LaneChangeMsgs',
            self.lanechange_output_callback,
            10
        )
        self.subscription_lanchange

        self.frame_heartbeat_period = 10.0 # 10.0 second
        self.frame_heartbeat_timer = self.create_timer(self.frame_heartbeat_period,
            self.frame_heartbeat_callback)
        
        self.frame_id = 0
        self.clock = rclpy.clock.ROSClock()
        self.pub_sim_tick = self.create_publisher(
            SimTick, 
            'SimTick', 
            10
        )
        self.pub_vehicle_resetinfo = self.create_publisher(
            VehicleModelReset,
            'VehicleModelReset',
            10
        )

    def run_one_tick(self):
        # update frame_id
        self.frame_id += 1
        [sec, nanosec] = self.clock.now().seconds_nanoseconds()

        tick = SimTick()
        tick.header.frame_id = str(self.frame_id)
        tick.header.stamp.sec = sec
        tick.header.stamp.nanosec = nanosec

        self.pub_sim_tick.publish(tick)

    def frame_heartbeat_callback(self):
        self.get_logger().info("timeout at tick {} !!!".format(self.frame_id ))

        self.run_one_tick()

    def vehicle_output_callback(self, msg):
        frame_id = int(msg.header.frame_id)
        if frame_id == -1:
            # this is init report
            return

        fuel_comp_metric = msg.comprehensive_metric
        fuel_total = msg.total_fuel

        print("finish sim tick : # {} , with fuel -c {:.4f}, -total {:.4f}".\
            format(self.frame_id, fuel_comp_metric, fuel_total))

        if frame_id == self.frame_id:
            # reset heart beat
            self.frame_heartbeat_timer.reset()

            self.run_one_tick()

    def lanechange_output_callback(self,msg):
        self.vehicle_state = {
            'x': -22.30784,
            'y': 20.9243,
            'z':  0.0,
            'pitch': 0.0,
            'yaw': 147.85,
            'roll': 0.0,
            'vx': 0.0,
            'vy': 0.0,
            'eng_trq_nm': 0.0,
            'eng_spd_rpm': 0.0,
            'gear_pos': 0.0,
        }
        
        if msg.done == True:
            reset_msg = VehicleModelReset()
            reset_msg.xo = self.vehicle_state['x']
            reset_msg.yo = self.vehicle_state['y']
            reset_msg.zo = self.vehicle_state['z']

            reset_msg.yaw = self.vehicle_state['yaw']
            reset_msg.roll = self.vehicle_state['roll']
            reset_msg.pitch = self.vehicle_state['pitch']

            reset_msg.vx = self.vehicle_state['vx']
            reset_msg.vy = self.vehicle_state['vy']

            reset_msg.eng_trq_nm = self.vehicle_state['eng_trq_nm']
            reset_msg.eng_spd_rpm = self.vehicle_state['eng_spd_rpm']
            reset_msg.gear_pos = self.vehicle_state['gear_pos']
            
            self.pub_vehicle_resetinfo.publish(reset_msg)
        
        else:
            pass

def main(args=None):
    rclpy.init(args=args)
    scenario_node = ScenarioJinan()
    rclpy.spin(scenario_node)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    scenario_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()