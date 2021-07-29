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
import time

import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Header

from fead_interfaces.msg import SimTick
from fead_interfaces.msg import VehicleModelOutput

#import carla

class ScenarioJinan(Node):

    def __init__(self):
        super().__init__('scenario_jinan')

        self.subscription = self.create_subscription(
            VehicleModelOutput,
            'VehicleModelOutput',
            self.vehicle_output_callback,
            10)
        self.subscription  # prevent unused variable warning

        self.frame_heartbeat_period = 10.0 # 10.0 second
        self.frame_heartbeat_timer = self.create_timer(self.frame_heartbeat_period,
            self.frame_heartbeat_callback)
        
        self.frame_id = 0
        self.clock = rclpy.clock.ROSClock()
        self.pub_sim_tick = self.create_publisher(SimTick, 'SimTick', 10)

        self.last_time = 0

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
        self.last_time = time.time()
        self.run_one_tick()

    def vehicle_output_callback(self, msg):
        frame_id = int(msg.header.frame_id)
        if frame_id == -1:
            # this is init report
            return

        fuel_comp_metric = msg.comprehensive_metric
        fuel_total = msg.total_fuel

        print("finish sim tick : # {} , with fuel -c {:.4f}, -total {:.4f}, FPS {:.4f}".\
            format(self.frame_id, fuel_comp_metric, fuel_total, 1/(time.time()-self.last_time)))
        self.last_time = time.time()
        if frame_id == self.frame_id:
            # reset heart beat
            self.frame_heartbeat_timer.reset()

            self.run_one_tick()
        

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