#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#

### offline lanechange planning 
import math, os
import numpy as np
from collections import deque


import pkg_resources
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

from tqdm import tqdm
from scipy import interpolate
import matplotlib.pyplot as plt

try:
    ##### for release #####
    from trajectory_planner.pcc.main import PCC_algorithm
    from trajectory_planner.HDMap_fake import HDmap
    from trajectory_planner.coord_tranform import Coord_Trans
except:
    #### for debug ######
    from HDMap_fake import HDmap
    from pcc.main import PCC_algorithm
    from coord_tranform import Coord_Trans

from ament_index_python.packages import get_package_share_directory
package_share_directory = get_package_share_directory('trajectory_planner')

from trajectory_planner.quintic_polynomials_planner import quintic_polynomials_planner

class LCRouting(Node):
    # add some contraint here
    def __init__(self):
        super().__init__('LCRouting')
        self._map = HDmap()

        self.candidiate_road_file = "/home/dawei/test/pcc/lane_change.txt"
        self.processed_file_dir = "/home/dawei/fead_ws/src/planning/trajectory_planner/trajectory_planner/lane_change_precessed.txt"
        ## trucksim coord start and end
        self.coord_trans = Coord_Trans(-225.151904, -6337.384475)

        self.lanechange_length = 10000 ## point number here, 10000 points means 100m
        self.lane_change_start_point_A = 10000
        self.lane_change_start_point_B = 112000

        self.x = []
        self.y = []
        self.z = []
        self.v = []

        self.read_candidiate_road()

        self.speed_planner = PCC_algorithm()

        self.target_speed = 16.67

    
    def run_step(self, start_point, change_length, lc_op):
        self.x = np.array(self.x)
        self.y = np.array(self.y)
        self.z = np.array(self.z)
        self.v = np.array(self.v)

        x_before_change = self.x[:start_point]
        y_before_change = self.y[:start_point]
        z_before_change = self.z[:start_point]
        v_before_change = self.v[:start_point]
        
        x_after_change = self.x[start_point+change_length:]
        y_after_change = self.y[start_point+change_length:]
        z_after_change = self.z[start_point+change_length:]
        v_after_change = self.v[start_point+change_length:]

        ## for qurey z axis after polynomials_planner, because we only have xy in polynomials_planner
        x_changing = self.x[start_point:start_point+change_length]
        y_changing = self.y[start_point:start_point+change_length]
        z_changing = self.z[start_point:start_point+change_length]
        v_changing = self.v[start_point:start_point+change_length]
        xy_z_changing = interpolate.interp2d(x_changing, y_changing, z_changing)

        sx = x_before_change[-1]  # start x position [m]
        sy = y_before_change[-1]  # start y position [m]
        ## we need to know the yaw angle here!!!
        syaw = np.deg2rad(10.0)  # start yaw angle [rad]
        sv = v_before_change[-1]  # start speed [m/s]
        sa = 0.0  # start accel [m/ss]

        if lc_op == "left":
            lc_waypoint = self._map.query_right_lane(self.coord_trans.trucksim_to_map(x_after_change[0], y_after_change[0])+[z_after_change[0]])
        else:
            lc_waypoint = self._map.query_left_lane(self.coord_trans.trucksim_to_map(x_after_change[0], y_after_change[0])+[z_after_change[0]])

        if lc_waypoint is None:
            print("error!! no right/left lane for LC!!, returned")
            return
        else:
            [gx, gy,_] = lc_waypoint

        ## we need to know the yaw angle here!!!
        #gyaw = np.deg2rad(20.0)  # goal yaw angle [rad]
        gyaw = 2.5808587705806447
        gv = v_before_change[-1] # goal speed [m/s]
        ga = 0.0  # goal accel [m/ss]

        max_accel = 1.0  # max accel [m/ss]
        max_jerk = 0.5  # max jerk [m/sss]
        dt = 0.1  # time tick [s]

        time, x, y, yaw, v, a, j = quintic_polynomials_planner(sx, sy, syaw, sv, sa, gx, gy, gyaw, gv, ga, max_accel, max_jerk, dt)

        if lc_op == "left":
            new_dest_waypoint = self._map.query_right_lane(self.coord_trans.trucksim_to_map(x_after_change[-1], y_after_change[-1])+[z_after_change[-1]])
        else:
            new_dest_waypoint = self._map.query_left_lane(self.coord_trans.trucksim_to_map(x_after_change[-1], y_after_change[-1])+[z_after_change[-1]])

        if new_dest_waypoint is None:
            print("error!! no right/left lane for GP!!")
            return
        else:
            [dest_x, dest_y, dest_z] = new_dest_waypoint

        print(lc_waypoint)
        print(new_dest_waypoint)
    
        new_gp = self._map.GlobalPlanner_waypoints(self.coord_trans.trucksim_to_map(lc_waypoint[0], lc_waypoint[1])+[lc_waypoint[2]],\
             self.coord_trans.trucksim_to_map(new_dest_waypoint[0],new_dest_waypoint[1])+[new_dest_waypoint[2]])

        ## reconstruction of xyzv plan
        self.x = []
        self.y = []
        self.z = []
        self.v = []
        ## waypoints before lane change
        for ix, iy, iz, iv in zip(x_before_change, y_before_change, z_before_change, v_before_change):
            self.x.append(ix)
            self.y.append(iy)
            self.z.append(iz)
            self.v.append(iv)

        # waypoints in lane change
        for ix, iy, iv in zip(x, y, v):
            self.x.append(ix)
            self.y.append(iy)
            self.z.append(xy_z_changing(ix, iy)[0])
            self.v.append(iv)

        # new routing after lane change
        grad_x, grad = self._map.query_gradient(new_gp)
        x_gp = []
        y_gp = []
        for itm in new_gp:
            x_gp.append(itm[0])
            y_gp.append(itm[1])
            
        step_size = 1000
        grad_x_step = np.array(grad_x[0:-1:step_size])
        grad_step = grad[0:-1:step_size]
        pcc_v, pcc_x = self.speed_planner.pcc_speed_planner(grad_x_step.tolist(), grad_step, self.target_speed)
        pcc_v_f = interpolate.interp1d(pcc_x, pcc_v, kind='linear', fill_value='extrapolate')
        xy_xp = interpolate.interp2d(x_gp[0:-1:step_size], y_gp[0:-1:step_size],grad_x[0:-1:step_size])

        for i in range(len(new_gp)):
            self.x.append(new_gp[i][0])
            self.y.append(new_gp[i][1])
            self.z.append(new_gp[i][2])
            self.v.append(pcc_v_f(xy_xp(new_gp[i][0], new_gp[i][1]))[0])

    def write_planning_result(self):
        with open(self.processed_file_dir, "w") as f:
            for i in range(len(self.x)):
                write_line = str(self.x[i])+" "+str(self.y[i])+" "+str(self.z[i])+" "+str(self.v[i])+"\n"
                f.write(write_line)

    def read_candidiate_road(self):
        with open(self.candidiate_road_file, "r") as f:
            for line in f.readlines():
                processed_line = line.split( )
                self.x.append(float(processed_line[0]))
                self.y.append(float(processed_line[1]))
                self.z.append(float(processed_line[2]))
                self.v.append(float(processed_line[3]))

    def process(self):
        self.run_step(self.lane_change_start_point_A,self.lanechange_length,"left")
        # self.run_step(self.lane_change_start_point_B,self.lanechange_length,"right")
        self.write_planning_result()

def main(args=None):
    rclpy.init(args=args)
    opnd = LCRouting()
    opnd.process()
    opnd.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    #main()
    opnd = LCRouting()
    opnd.process()