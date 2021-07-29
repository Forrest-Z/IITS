#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
from ament_index_python.packages import get_package_share_directory
from traffic_sim.preprocss import get_car_information
import time
import math
import os
import rclpy
from rclpy.node import Node


from fead_interfaces.msg import SimTick, Obstacle, PredictionResult, PerceptionResult, TrafficListMsg
from geometry_msgs.msg import Vector3
import std_msgs
import numpy as np

from collections import deque
#import pkg_resources

######################################
######################################
node_name = 'traffic_sim'

node_share_dir = get_package_share_directory(node_name)

#traffic_sample_dir = os.path.join(node_share_dir, 'trafficData_mapped/twoLanes/sample4_selected')
# traffic_sample_dir = os.path.join(node_share_dir, 'trafficData_mapped_angle/twoLanes/Fast/sample1_selected_10km')
traffic_sample_dir = os.path.join(
    node_share_dir, 'trafficData_mapped_angle/twoLanes/constantDistance/sample4')
#traffic_sample_dir = os.path.join(node_share_dir, 'trafficData_mapped/twoLanes/montage1')

######################################
######################################


class TrafficAgent():
    def __init__(self, id, data_file):
        self.id = id
        self.data_file = data_file
        self.load_data()

    def load_data(self):
        self.x, self.y, self.z, self.lane_ids, self.yaw = get_car_information(
            self.data_file)
        assert len(self.x) == len(self.y)
        assert len(self.x) == len(self.z)
        assert len(self.x) == len(self.lane_ids)

        self.frame_num = len(self.x)
        self.pitch = [0.0] * self.frame_num
        #self.yaw = [0.0] * self.frame_num
        self.roll = [0.0] * self.frame_num

    def get(self, frame_id):
        frame_id = frame_id % self.frame_num
        return {'x': self.x[frame_id], 'y': self.y[frame_id], 'z': self.z[frame_id],
                'pitch': self.pitch[frame_id], 'yaw': self.yaw[frame_id],
                'roll': self.roll[frame_id], 'lane_ids': self.lane_ids[frame_id]}


class TrafficSim(Node):
    def __init__(self):
        super().__init__(node_name)
        self.prediction_length = 10
        self.pub_prediction = self.create_publisher(
            PredictionResult, 'PredictionResult', 10)
        self.subscription = self.create_subscription(SimTick, 'SimTick',
                                                     self.sim_tick_callback, 10)
        self.subscription_traffic_list = self.create_subscription(TrafficListMsg, 'TrafficListMsg',
                                                                  self.traffic_list_callback, 10)
        self.subscription  # prevent unused variable warning
        self.subscription_traffic_list
        self.traffic_list = []

        self.load_traffic_file(traffic_sample_dir)

        self.traffic_speed_smooth_window_size = 10

    def sim_tick_callback(self, msg):
        data = self.gen_prediction_data(msg.header)
        # data = self.gen_empty_prediction_data(msg.header)
        self.pub_prediction.publish(data)

    def traffic_list_callback(self, msg):
        self.traffic_list = []
        for itm in msg.traffic_list:
            self.traffic_list.append(itm)

    def gen_empty_prediction_data(self, header):
        prediction_result = PredictionResult()
        prediction_result.header = header

        req_frame_id = int(header.frame_id)
        for frame_id in range(req_frame_id, req_frame_id + self.prediction_length):
            perception_data = PerceptionResult()
            perception_data.header.frame_id = str(frame_id)
            prediction_result.frame.append(perception_data)
        return prediction_result

    def gen_prediction_data(self, header):
        prediction_result = PredictionResult()
        prediction_result.header = header

        req_frame_id = int(header.frame_id)
        for frame_id in range(req_frame_id, req_frame_id + self.prediction_length):
            perception_data = PerceptionResult()
            perception_data.header.frame_id = str(frame_id)

            # for agent in self.agents.values():
            for v_id in self.traffic_list:
                agent = self.agents[v_id]
                data = agent.get(frame_id)

                obstacle = Obstacle()
                obstacle.id = str(agent.id)
                obstacle.center = Vector3(
                    x=data['x'], y=data['y'], z=data['z'])
                obstacle.yaw = data['yaw']
                if frame_id > self.traffic_speed_smooth_window_size:
                    delta_s = 0
                    for fid in range(frame_id - self.traffic_speed_smooth_window_size+1, frame_id+1):
                        pre_data = agent.get(fid - 1)
                        this_dta = agent.get(fid)
                        delta_s += math.sqrt(math.pow(this_dta['x'] - pre_data['x'], 2)
                                             + math.pow(this_dta['y'] - pre_data['y'], 2)
                                             + math.pow(this_dta['z'] - pre_data['z'], 2))
                        obstacle.speed = delta_s / \
                            (0.1 * self.traffic_speed_smooth_window_size)
                elif frame_id > 1:
                    delta_s = 0
                    for fid in range(1, frame_id+1):
                        pre_data = agent.get(fid - 1)
                        this_dta = agent.get(fid)
                        delta_s += math.sqrt(math.pow(this_dta['x'] - pre_data['x'], 2)
                                             + math.pow(this_dta['y'] - pre_data['y'], 2)
                                             + math.pow(this_dta['z'] - pre_data['z'], 2))
                        obstacle.speed = delta_s / (0.1 * (frame_id))
                else:
                    obstacle.speed = 0.0

                perception_data.obstacles.append(obstacle)
            prediction_result.frame.append(perception_data)
        return prediction_result

    def load_traffic_file(self, traffic_sample_dir):

        info_file_path = os.path.join(traffic_sample_dir, 'info.txt')
        print(info_file_path)
        assert os.path.isfile(info_file_path)

        f_info = open(info_file_path, 'r')
        line = f_info.readline()
        line = line[:-1]
        self.vehicle_num = int(line.split(' ')[0])
        self.frame_num = int(line.split(' ')[2])

        self.agents = {}
        for vehicle_id in range(self.vehicle_num):
            data_file = os.path.join(
                traffic_sample_dir, str(vehicle_id) + '.txt')
            assert os.path.isfile(data_file)

            self.agents[vehicle_id] = TrafficAgent(vehicle_id, data_file)
            assert self.frame_num == self.agents[vehicle_id].frame_num

    def save_ego_trajectory(self, player):
        self.text_create(str(player.get_location().x)+" "+str(player.get_location().y) +
                         " "+str(player.get_location().z)+" "+str(self.frameID)+"\n", self.name)

    def text_create(self, msg, name):
        desktop_path = "./"
        full_path = os.path.join(desktop_path + name)
        file = open(full_path, 'a')
        file.write(msg)


################## main entrance ######################
def main(args=None):
    rclpy.init(args=args)
    traffic_sim_node = TrafficSim()
    rclpy.spin(traffic_sim_node)
    traffic_sim_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
