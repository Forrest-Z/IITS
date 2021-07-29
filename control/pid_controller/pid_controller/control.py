#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
import queue, time, math
import sys
sys.path.append("../")
import numpy as np
from collections import deque
import time

import rclpy
from rclpy.node import Node
from threading import Thread

##TODO PnC interface here 
from fead_interfaces.msg import PlanningResult 
from fead_interfaces.msg import VehicleModelInput, VehicleModelOutput
from fead_interfaces.srv import Control as ControlService
from fead_interfaces.msg import LaneChangeMsgs, VehicleModelReset

try:
    from pid_controller import VehiclePIDController, AccTothrottle
    from fuelmodel_dongfeng import FuelModel
except:
    from pid_controller.pid_controller import VehiclePIDController, AccTothrottle
    from pid_controller.fuelmodel_dongfeng import FuelModel

from ad_map_server_py.ad_map_server import MapServer, CoordTrans

def compute_distance(loc1, loc2):
    assert len(loc1) == len(loc2)
    if len(loc1) == 2:
        return math.sqrt((loc1[0]-loc2[0])**2+(loc1[1]-loc2[1])**2)
    if len(loc1) == 3:
        return math.sqrt((loc1[0]-loc2[0])**2+(loc1[1]-loc2[1])**2+(loc1[2]-loc2[2])**2)
    

class ControllerNode(Node):
    def __init__(self):
        super().__init__('ControllerNode')
        self.node = self
        self.init_stage = True
        self.planner_result = None
        self.controller = VehiclePIDController()
        MapServer()
        self.coord_trans = CoordTrans()
        self._buffer_size = 10000
        self._waypoint_buffer = deque(maxlen=self._buffer_size)

        self.frame_id = 0

        self.emergency_stop = False
        self.acctotho = AccTothrottle(0.8, 0.008, 0.0000256, 1.225, 7, 9000)

        self.vehicle_state = { 'x': 0.0,
            'y': 0.0,
            'z': 0.0,
            'pitch': 0.0,
            'yaw': 0.0,
            'roll': 0.0,
            'vx': 0.0,
            'vy': 0.0,
            'eng_trq_nm': 0.0,
            'eng_spd_rpm': 0.0,
            'gear_pos': 0.0,
            }

        self.last_vehicle_output_msg = None

        self.VEHICLE_SIM_TIME = 0.01
        self.PLANNING_SIM_TIME = 0.1
        self.CONTROL_SIM_FRAMES = int(self.PLANNING_SIM_TIME / self.VEHICLE_SIM_TIME) # 10

        self.timer_period = self.VEHICLE_SIM_TIME

        ###########################################
        # interface between control & planning
        self.sub_planning_result = self.create_subscription(
            PlanningResult,
            "planning_result",
            self.planner_result_callback,
            10
        )

        self.pub_vehicle_output = self.create_publisher(
            VehicleModelOutput,
            'VehicleModelOutput',
            10)

        self.pub_vehicle_output_debug = self.create_publisher(
            VehicleModelOutput,
            'VehicleModelOutput_Debug',
            10)

        self.subscription_lanchange_op = self.create_subscription(
                                                        VehicleModelReset,
                                                        'VehicleModelReset',
                                                        self.vehicle_reset_callback,
                                                        10
                                                        )

        self.cli_vehicle_control = self._create_client(ControlService, 'Control')

        ###########################################
        self.fuel_model = FuelModel(self.VEHICLE_SIM_TIME)

        self.comprehensive_metric = 0

    def vehicle_reset_callback(self,msg):
        self.init_stage = True
        self.planner_result = None

    def _create_client(self, service_tocall, service_name):
        service = self.node.create_client(service_tocall, service_name)
        while not service.wait_for_service(timeout_sec=0.1):
            self.node.get_logger().info('service '+service_name+ ' not available, waiting again...')
        self.node.get_logger().info('connected to service '+service_name)
        return service

    def init_report(self):
        req = ControlService.Request()
        req.input = self.gen_control_message(0.0, 0.0, 0.0)
        req.input.control_frame_id = -1 

        result = self.cli_vehicle_control.call_async(req)
        rclpy.spin_until_future_complete(self.node, result)

        if result.result() is not None:
            self.update_vehicle_response(result.result().output)

            self.last_vehicle_output_msg.header.frame_id = '-1'
            self.pub_vehicle_output.publish(self.last_vehicle_output_msg)
    
    def find_next_waypoint(self, vehicle_velocity):
        """
        function : find next waypoint
        method: 1.Get the driving distance of the vehicle in a timestamp
                2.Get the first point father than the travel distance of the current vehicle by a time stamp
        """
        delta_s = vehicle_velocity * self.timer_period
        accumulated_distance = compute_distance([self.vehicle_state['x'], self.vehicle_state['y'], self.vehicle_state['z']],
            [self._waypoint_buffer[0].center.x,self._waypoint_buffer[0].center.y,self._waypoint_buffer[0].center.z ])
        for i in range(len(self._waypoint_buffer)-1):
            if accumulated_distance > delta_s:
                return i
            accumulated_distance += compute_distance([self._waypoint_buffer[i].center.x,self._waypoint_buffer[i].center.y,self._waypoint_buffer[i].center.z ],\
                 [self._waypoint_buffer[i+1].center.x,self._waypoint_buffer[i+1].center.y,self._waypoint_buffer[i+1].center.z ])

    def get_target_speed(self, distance, time_period, current_speed):
        a = ((distance - current_speed * time_period) * 2) /math.pow(time_period, 2)
        return current_speed + a*time_period 

    def get_distance(self, waypoint, vehicle_state):
        delta_x = waypoint.center.x - vehicle_state['x']
        delta_y = waypoint.center.y - vehicle_state['y']
        delta_z = waypoint.center.z - vehicle_state['z']

        distance = math.sqrt(math.pow(delta_x, 2) + math.pow(delta_y, 2) + math.pow(delta_z, 2)) 
        return distance

    def run_one_control_session(self):
        import copy
        def check_waypoint_behind_me(waypoint, vehicle_location, vehicle_rotation):
            v_begin = np.array(vehicle_location)
            v_end = v_begin + np.array([math.cos(math.radians(vehicle_rotation)),
                                            math.sin(math.radians(vehicle_rotation)),0])
            v_vec = np.array([v_end[0] - v_begin[0], v_end[1] - v_begin[1], 0.0])
            w_vec = np.array([waypoint[0] -
                            v_begin[0], waypoint[1] -
                            v_begin[1], 0.0])
            if np.clip(np.dot(w_vec, v_vec) /
                                    (np.linalg.norm(w_vec) * np.linalg.norm(v_vec)), -1.0, 1.0)< 0:
                                    return True
            return False

        last_transform = copy.deepcopy(self.vehicle_state)
        next_waypoint = self._waypoint_buffer.popleft()
        for frame_id in range(self.CONTROL_SIM_FRAMES):

            vehicle_velocity = math.sqrt(self.vehicle_state['vx']**2 + self.vehicle_state['vy']**2)
            vehicle_location = [self.vehicle_state['x'], self.vehicle_state['y'], self.vehicle_state['z']]
            vehicle_rotation = self.vehicle_state['yaw']

            dist = self.get_distance(next_waypoint, self.vehicle_state)
            target_speed = self.get_target_speed(dist , self.PLANNING_SIM_TIME - self.VEHICLE_SIM_TIME*frame_id, vehicle_velocity)

            target_speed = next_waypoint.speed

            next_waypoint_center = next_waypoint.center
            next_lateral_target_center = next_waypoint_center
            i = 1
            while check_waypoint_behind_me([next_lateral_target_center.x, next_lateral_target_center.y], vehicle_location, vehicle_rotation)\
                and i < len(self._waypoint_buffer)-2:
                next_lateral_target_center = self._waypoint_buffer[i].center
                i += 1

            if check_waypoint_behind_me([next_lateral_target_center.x, next_lateral_target_center.y], vehicle_location, vehicle_rotation):
                print("control: all waypoint behind me returned !!")
                return
            steering, delta_v, brake = self.controller.run_step(target_speed, \
                [next_lateral_target_center.x, next_lateral_target_center.y], \
                vehicle_velocity , vehicle_location, vehicle_rotation)

            throttle = delta_v

            req = ControlService.Request()
            req.input = self.gen_control_message(throttle, steering, brake)
            req.input.control_frame_id = frame_id

            result = self.cli_vehicle_control.call_async(req)
            rclpy.spin_until_future_complete(self, result)

            if result.result() is not None:
                self.update_vehicle_response(result.result().output)

    def update_vehicle_response(self, vehicle_output_msg):
        ## we change all location into map coordinate
        car_pos_map = self.coord_trans.trucksim_to_map([vehicle_output_msg.xo, vehicle_output_msg.yo, vehicle_output_msg.zo])
        vehicle_output_msg.xo = car_pos_map[0]
        vehicle_output_msg.yo = car_pos_map[1]
        vehicle_output_msg.zo = car_pos_map[2]
        
        self.last_vehicle_output_msg = vehicle_output_msg

        # update state
        self.vehicle_state['x'] = vehicle_output_msg.xo
        self.vehicle_state['y'] = vehicle_output_msg.yo
        self.vehicle_state['z'] = vehicle_output_msg.zo
        self.vehicle_state['pitch'] = vehicle_output_msg.pitch
        self.vehicle_state['yaw'] = vehicle_output_msg.yaw
        self.vehicle_state['roll'] = vehicle_output_msg.roll
        self.vehicle_state['vx'] = vehicle_output_msg.vx
        self.vehicle_state['vy'] = vehicle_output_msg.vy
        self.vehicle_state['vz'] = vehicle_output_msg.vz
        self.vehicle_state['eng_trq_nm'] = vehicle_output_msg.eng_trq_nm
        self.vehicle_state['eng_spd_rpm'] = np.clip(vehicle_output_msg.eng_spd_rpm, 600, 2150)
        self.vehicle_state['gear_pos'] = np.clip(vehicle_output_msg.gear_pos, 2, 12)
        
        # update fuel info 
        self.total_fuel, self.fuel_rate, self.comprehensive_metric = self.fuel_model.calc_metric(
            self.vehicle_state['eng_trq_nm'], self.vehicle_state['eng_spd_rpm'], 
                math.sqrt(self.vehicle_state['vx']**2 + self.vehicle_state['vy']**2))
        # self.last_vehicle_output_msg.total_fuel = self.total_fuel
        self.last_vehicle_output_msg.fuel_rate = self.fuel_rate
        self.last_vehicle_output_msg.comprehensive_metric = self.comprehensive_metric

        # for debug
        self.pub_vehicle_output_debug.publish(self.last_vehicle_output_msg)

    def gen_control_message(self, throttle = 0.0, steering = 0.0, brake = 0.0):
        ctrl_msg = VehicleModelInput()

        # scale data
        throttle = throttle * 100.0
        steering = steering * 6.0

        vehicle_velocity = math.sqrt(self.vehicle_state['vx']**2 + self.vehicle_state['vy']**2)
        if vehicle_velocity < 1.0:
            vehicle_velocity = 1.0

        if vehicle_velocity > 100.0 or self.emergency_stop:
            throttle = 0.0
            brake = -6.0
        
        ctrl_msg.brake = brake
        if brake != 0.0:
            ctrl_msg.ctrlmode = 2.0
        else:
            ctrl_msg.ctrlmode = 0.0
    
        ctrl_msg.throttle = throttle
        ctrl_msg.steer = steering

        return ctrl_msg

    def planner_result_callback(self, planning_result_msg):
        if self.init_stage == True:
            self.init_stage = False

        # store planning result
        self.planner_result= planning_result_msg

    def run_once(self):
        
        if self.init_stage == True:
            self.init_report()

        if self.planner_result is not None:
            planning_result_msg = self.planner_result
            self.planner_result = planning_result_msg.waypoints

            self.frame_id = int(planning_result_msg.header.frame_id)
        
            if len(self.planner_result) >= 0:
                # clear previous buffer
                self._waypoint_buffer = deque(maxlen=self._buffer_size)

            for point in self.planner_result:
                self._waypoint_buffer.append(point)
            self.emergency_stop = planning_result_msg.emergency_stop

            self.run_one_control_session()

            self.last_vehicle_output_msg.header = planning_result_msg.header
            self.pub_vehicle_output.publish(self.last_vehicle_output_msg)
            self.planner_result = None


def main(args = None):
    rclpy.init(args = args)
    controller_node = ControllerNode()
    while rclpy.ok():
        rclpy.spin_once(controller_node, timeout_sec = 0.001)
        controller_node.run_once()
    controller_node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()