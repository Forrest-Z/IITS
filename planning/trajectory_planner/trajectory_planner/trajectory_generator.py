#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#

### trajectory planning 
import math
import numpy as np
import os, time, sys
from collections import deque
#from trajectory_planner.controller import VehiclePIDController
# from trajectory_planner.pcc.main import PCC_algorithm
import pkg_resources
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

try:
    # from HDMap import HDmap
    sys.path.append('/home/dawei/fead_ws/src/hdmap/ad_map/ad_map_server_py/ad_map_server_py')
    from ad_map_server import MapServer
except:
    # from trajectory_planner.HDMap import HDmap
    from ad_map_server_py.ad_map_server import MapServer
# from trajectory_planner.HDMap import HDmap as GPmap

# from ad_map_server_py.ad_map_server import MapServer, CoordTrans

from fead_interfaces.msg import LaneChangeMsgs
from fead_interfaces.msg import Obstacle, PredictionResult, PerceptionResult
from fead_interfaces.msg import VehicleModelOutput, VehicleModelInput, VehicleModelReset
from fead_interfaces.msg import PlanningResult, Waypoint

from trajectory_planner.quintic_polynomials_planner import quintic_polynomials_planner
# from trajectory_planner.coord_tranform import Coord_Trans
from trajectory_planner.offline_pcc import PCCReader2, PCCReader

from ament_index_python.packages import get_package_share_directory
package_share_directory = get_package_share_directory('trajectory_planner')

class TrajectoryPlanner(Node):
    # add some contraint here
    def __init__(self, start_point, end_point):
        super().__init__('trajectory_generator')
        self._map = MapServer()
        self.car_following_sign = False

        self.planner_mode = "PCC"

        self.start_point = start_point
        self.end_point = end_point
       
        self._collsion_avoidance_distance = 10.0
        self._lane_change_distance = 100.0

        self._car_following_distance = 50.0
        self._car_following_keep_dist = 30.0
        self._car_following_response_time = 150 ## 5 ticks here 


        self.fps = 10

        self._buffer_size = 10000
        self._vehicle = None # x y roll pitch yaw vx vy
        self._waypoint_buffer = deque(maxlen=10000)
        self._speed_profile = deque(maxlen=10000)
        self.emergency_stop = False

        self.prediction_msg_buffer = []
        
        ## for lane change algorithm
        self.lc_status = 0
        self.lc_counter = 0
        self.lc_dest = None


        ## planner status 0=cruise, 1=car following, 2 = emergency_stop
        self.planner_status = 0
        self.pcc_reader = PCCReader2()
        
        self.vehicle_list = None
        self.vehicle_state = {
            'x': -252.6831285,
            'y': -6325.0292965,
            'z':  297.536682,
            'pitch': 0.0,
            'yaw': 0.0,
            'roll': 0.0,
            'vx': 0.0,
            'vy': 0.0,
            'eng_trq_nm': 0.0,
            'eng_spd_rpm': 0.0,
            'gear_pos': 0.0,
            'ready':False
            }
        
        ## for experiment logger
        self.delta_v_percent = []
        self.brake_times = 0
        self.lc_count_log = 0
        self.logfile = open("exp_logfile.txt","w")

        self.subscribe_perception = self.create_subscription(
            PredictionResult,
            'PredictionResult',
            self.perception_callback,
            10)
        
        self.subscribe_dm = self.create_subscription(
            LaneChangeMsgs,
            'LaneChangeMsgs',
            self.lane_change_callback,
            10
        )

        self.subscrbe_vehcile_reset = self.create_subscription(
            VehicleModelReset,
            'VehicleModelReset',
            self.vehicle_reset_callback,
            10
        )

        self.subscription_trucksim = self.create_subscription(
            VehicleModelOutput,
            'VehicleModelOutput',
            self.trucksim_output_callback,
            10)

        self.publisher=self.create_publisher(
            PlanningResult,
            "planning_result",
            10
        )

    def trucksim_output_callback(self, trucksim_output_msg):
        """
        Get the status of the own car
        """
        ## add z axis
        self._vehicle = [trucksim_output_msg.xo, trucksim_output_msg.yo, trucksim_output_msg.zo,\
            trucksim_output_msg.roll,trucksim_output_msg.pitch, trucksim_output_msg.yaw,\
                trucksim_output_msg.vx,trucksim_output_msg.vy]
        # update state
        self.vehicle_state['x'] = trucksim_output_msg.xo
        self.vehicle_state['y'] = trucksim_output_msg.yo
        self.vehicle_state['z'] = trucksim_output_msg.zo
        self.vehicle_state['pitch'] = trucksim_output_msg.pitch
        self.vehicle_state['yaw'] = trucksim_output_msg.yaw
        self.vehicle_state['roll'] = trucksim_output_msg.roll
        self.vehicle_state['vx'] = trucksim_output_msg.vx
        self.vehicle_state['vy'] = trucksim_output_msg.vy
        self.vehicle_state['eng_trq_nm'] = trucksim_output_msg.eng_trq_nm
        self.vehicle_state['eng_spd_rpm'] = trucksim_output_msg.eng_spd_rpm
        self.vehicle_state['gear_pos'] = trucksim_output_msg.gear_pos
        self.vehicle_state['ready'] = True
        
    def vehicle_reset_callback(self, msg): 
        self.lc_status = 0.0
        self.lc_counter = 0.0
        self.vehicle_state['ready'] = False

        self.delta_v_percent = np.array(self.delta_v_percent)
        ava_delta = self.delta_v_percent.mean()
        self.logfile.write("delta_v:"+str(ava_delta)+" lc_count:"+str(self.lc_count_log)+" brake_time:"+str(self.brake_times)+"\n")
        self.logfile.flush()
        print("delta_v:"+str(ava_delta)+" lc_count:"+str(self.lc_count_log)+" brake_time:"+str(self.brake_times)+"\n")

        self.delta_v_percent = []
        self.brake_times = 0
        self.lc_count_log = 0

    def perception_callback(self, msg):
        self.prediction_msg_buffer = msg.frame

    def lane_change_callback(self, msg):
        """
        function:Determine whether to brake or change lanes according to the state of the surrounding cars
        method:1.Determine whether to emergency stop according to the state of the surrouding cars
               2.Determine whether to lane change according to the states of the surrounding cars
        """

        begin_time = time.time()
        if self.vehicle_state['ready'] == False:
            return 

        if self.prediction_msg_buffer == None or len(self.prediction_msg_buffer) == 0:
            self.vehicle_list = []
        else:
            self.vehicle_list = self.prediction_msg_buffer[0].obstacles
        
        collision_risk = self.collsion_detection(self.vehicle_list, self._collsion_avoidance_distance, 15.0)
        # collision_risk = False

        ## if there is collision risk in front of ego car, send emergency stop sign to control
        if collision_risk:
            print("collision risk")
            self.emergency_stop = True
            self.brake_times += 1
        else:
            self.emergency_stop = False
        if len(self._speed_profile)>0:
            pcc_v = self.pcc_reader.qurey_v(self.vehicle_state['x'], self.vehicle_state['y'])
            self.delta_v_percent.append((pcc_v-self.vehicle_state['vx'])/pcc_v)
        ## run trajectory planning and generate waypoints and speed profile
        self.run_step(msg.lanechangeop,self.vehicle_list)

        if self.emergency_stop == True:
            self.planner_status = 2
        ## send planning result to control module
        planning_result = PlanningResult()
        planning_result.header = msg.header
        if len(self._waypoint_buffer) == 0:
            print("reach the goal, returned ")
            return
        for speed, point in zip(self._speed_profile, self._waypoint_buffer):
            waypoint = Waypoint()
            waypoint.speed = float(speed)
            waypoint.center.x = point[0]
            waypoint.center.y = point[1]
            waypoint.center.z = point[2]
            planning_result.waypoints.append(waypoint)
        planning_result.emergency_stop = self.emergency_stop
        planning_result.planner_status = float(self.planner_status)
        self.publisher.publish(planning_result)

    def check_control(self):
        def compute_distance(loc1, loc2):
            return math.sqrt((loc1[0]-loc2[0])**2+(loc1[1]-loc2[1])**2)
        if len(self._waypoint_buffer)<1:
            return
        ego_vehicle_location = [self.vehicle_state['x'],self.vehicle_state['y'],self.vehicle_state['z']]
        dist0 = compute_distance(ego_vehicle_location, self._waypoint_buffer[0])
        dist1 = compute_distance(ego_vehicle_location, self._waypoint_buffer[1])
        if dist0 > dist1:
            print("Too fast!!"+str(dist0))
        else:
            print("Too slow!!"+str(dist1))

    def run_step(self, propose_lane_change, vehicle_list):

        if propose_lane_change == -1.0 or propose_lane_change == 1.0 or self.lc_status != 0:
            self.lane_changing(propose_lane_change)
        else:
            self.lane_keeping()

        if len(self._waypoint_buffer) == 0:
            self.lane_keeping()

    def check_waypoint_lateral(self, waypoints, vehicle_location, vehicle_rotation):
        i = 0
        waypoint = waypoints[i]
        while i < len(waypoints)-2:
            v_begin = np.array(vehicle_location)
            v_end = v_begin + np.array([math.cos(math.radians(vehicle_rotation)),
                                            math.sin(math.radians(vehicle_rotation)),0])

            v_vec = np.array([v_end[0] - v_begin[0], v_end[1] - v_begin[1], 0.0])
            w_vec = np.array([waypoint[0] -
                            v_begin[0], waypoint[1] -
                            v_begin[1], 0.0])
            if np.clip(np.dot(w_vec, v_vec) /
                                    (np.linalg.norm(w_vec) * np.linalg.norm(v_vec)), -1.0, 1.0)< 0:
                if i > len(waypoints)-3:
                    return True
                else:
                    i += 1
                    waypoint = waypoints[i]
            else:
                break
        return False

    def collsion_detection(self,vehicle_list,threshold,angle):
        """
        Collsion Detection
        """
        def is_within_distance_ahead(target_location, current_location, orientation, max_distance, angle):
            """
            Determine whether the vehicle ahead isn within the specified range
            """
            target_vector = np.array([target_location[0] - current_location[0], target_location[1] - current_location[1]])
            norm_target = np.linalg.norm(target_vector)
            # If the vector is too short, we can simply stop here
            if norm_target < 0.001:
                return True
            if norm_target > max_distance:
                return False
            #angle to radian
            forward_vector = np.array([math.cos(math.radians(orientation)), math.sin(math.radians(orientation))])

            d_angle = math.degrees(math.acos(np.dot(forward_vector, target_vector) / norm_target))
            return d_angle < angle

        ego_vehicle_location = [self.vehicle_state['x'],self.vehicle_state['y'],self.vehicle_state['z']]
        ego_vehicle_location = ego_vehicle_location
        for target_vehicle in vehicle_list:
            target_location = [target_vehicle.center.x, target_vehicle.center.y]
            if is_within_distance_ahead(target_location, ego_vehicle_location,
                                        self.vehicle_state['yaw'],threshold, angle):
                print("hazard!!!"+str(target_vehicle.center)+"my location "+str(ego_vehicle_location))
                return True
        return False

    def lane_keeping(self):
        """
        lane keeping
        """
        def check_buffer(buffer):
            speed = []
            for i in range(len(buffer)-1):
                speed.append(math.sqrt((buffer[i][0]-buffer[i+1][0])**2+(buffer[i][1]-buffer[i+1][1])**2+(buffer[i][2]-buffer[i+1][2])**2)/0.1)
            return speed
        vehicle_location_map =[self.vehicle_state['x'], self.vehicle_state['y'],self.vehicle_state['z']]
        vehicle_rotation = self.vehicle_state['yaw']
        
        # check car following
        choosen_idx = None
        if self.car_following_sign:
            _, choosen_idx = self._map.find_front_cars(vehicle_location_map, self.vehicle_list, self._car_following_distance)
        if choosen_idx is None:
            self.planner_status = 0
            # no vehicle in front of the ego car
            if self.planner_mode == "const_speed":
                #const speed mode

                target_speed_const = 16.67
                waypt_interval = target_speed_const/self.fps
                waypt_num = int(self._lane_change_distance/waypt_interval)
                self._waypoint_buffer = self._map.cal_constv_pt(vehicle_location_map, self.end_point, waypt_num, waypt_interval)
                speed_check = check_buffer(self._waypoint_buffer)

                self._speed_profile = deque(maxlen=100000)
                for v in range(len(self._waypoint_buffer)):
                    self._speed_profile.append(target_speed_const)
            else:
                # pcc mode
                self._waypoint_buffer, self._speed_profile = self._map.cal_pcc_waypt(vehicle_location_map, self.end_point, self.pcc_reader, self._lane_change_distance, 1/self.fps)
                speed_check = check_buffer(self._waypoint_buffer)
                if self.check_waypoint_lateral(self._waypoint_buffer, vehicle_location_map, vehicle_rotation):
                    print("all waypoint is behind the ego car, replanned with const speed ")
                    target_speed_const = 16.67
                    waypt_interval = target_speed_const/self.fps
                    waypt_num = int(self._lane_change_distance/waypt_interval)
                    self._waypoint_buffer = self._map.cal_constv_pt(vehicle_location_map, self.end_point, waypt_num, waypt_interval)
                    self._speed_profile = deque(maxlen=100000)
                    for v in range(len(self._waypoint_buffer)):
                        self._speed_profile.append(target_speed_const)
                self._waypoint_buffer.popleft()
                self._speed_profile.popleft()
        else:
            self.planner_status = 1
            # there is a vehicle in front of ego car, using car following
            front_car_velocity = self.vehicle_list[choosen_idx].speed
            distance = math.sqrt((self.vehicle_list[choosen_idx].center.x-self.vehicle_state['x'])**2\
                +(self.vehicle_list[choosen_idx].center.y-self.vehicle_state['y'])**2)
            delta_velocity = (distance-self._car_following_keep_dist)*self.fps/(self._car_following_response_time)
            if front_car_velocity > 30.0:
                front_car_velocity = 30.0
            waypt_interval = (front_car_velocity+delta_velocity)/self.fps
            if waypt_interval <= 0:
                waypt_interval = 0.0001
                print("error!! front car velocity is 0!! or very close to us")
            waypt_num = int(self._lane_change_distance/waypt_interval)
            if waypt_num > 100:
                waypt_num = 100

            self._waypoint_buffer = self._map.cal_constv_pt(vehicle_location_map, self.end_point, waypt_num, waypt_interval)

            print("car following mode:"+str(self.vehicle_list[choosen_idx].id)+"target_speed:"+str(front_car_velocity)+"his location:"+str(self.vehicle_list[choosen_idx].center))
            self._speed_profile = deque(maxlen=100000)
            for _ in range(len(self._waypoint_buffer)):
                self._speed_profile.append(front_car_velocity+delta_velocity)

    def lane_changing(self, lc_op):
        def cal_yaw_rad(x0, y0, x1, y1):
            a = np.array([x1-x0, y1-y0])
            b = np.array([1,0])
            cosangle = a.dot(b)/(np.linalg.norm(a) * np.linalg.norm(b))
            yaw = math.acos(cosangle)
            if a[1]<0:
                yaw = 360-yaw
            return yaw

        # if lc is finished, reset lc_status 
        if self.lc_counter <=0:
            self.lc_status = 0

        #hyperparam for quintic_polynomials_planner
        max_accel = 100.0  # max accel [m/ss]
        max_jerk = 100.0  # max jerk [m/sss]
        dt = 1/self.fps  # time tick [s]
        vehicle_transform = [self.vehicle_state['x'], self.vehicle_state['y'], self.vehicle_state['z']]
        
        self.planner_status = 0

        if self.lc_status is not 0:        
            def compute_distance(loc1, loc2):
                return math.sqrt((loc1[0]-loc2[0])**2+(loc1[1]-loc2[1])**2)
            def update_waypoint(waypoints, vehicle_transform, min_dist):
                max_index = -1
                for i, waypt in enumerate(waypoints):
                    if compute_distance(waypt, vehicle_transform) < min_dist:
                        max_index = i
                if max_index >= 0:
                    for i in range(max_index + 1):
                        self._waypoint_buffer.popleft()
                        self._speed_profile.popleft()
                return max_index+1
            ## while lane changing is running
            ## tmply our control cannot following the waypoint in time
            lc_counter_minus = update_waypoint(self._waypoint_buffer, vehicle_transform, 1.0)
            self.lc_counter = self.lc_counter - lc_counter_minus
            lc_end_point = [self._waypoint_buffer[-1][0], self._waypoint_buffer[-1][1],self._waypoint_buffer[-1][2]]
            waypt_interval = 16.67/self.fps
            waypt_num = int(self._lane_change_distance/waypt_interval)
            if self.planner_mode == "const_speed": 
                waypt_bf_tmp = self._map.cal_constv_pt(lc_end_point,self.end_point, waypt_num, waypt_interval)
                speed_profile = [16.67 for i in range(1000)]
            else:
                waypt_bf_tmp, speed_profile = self._map.cal_pcc_waypt(lc_end_point,self.end_point,self.pcc_reader, self._lane_change_distance, 1/self.fps)
            for i in range(lc_counter_minus):
                if i+1>len(waypt_bf_tmp)-1:
                    break
                self._waypoint_buffer.append(waypt_bf_tmp[i+1])
                self._speed_profile.append(speed_profile[i+1])
        else:
            #rebuild a new buffer to garanttee lane chagne distance
            self.lc_count_log +=1

            vehicle_location_map = [self.vehicle_state['x'], self.vehicle_state['y'],self.vehicle_state['z']]
            target_speed_const = 16.67
            waypt_interval = target_speed_const/self.fps
            waypt_num = int(self._lane_change_distance/waypt_interval)
            self._waypoint_buffer = self._map.cal_constv_pt(vehicle_location_map, self.end_point, waypt_num, waypt_interval)
            self._waypoint_buffer.popleft()

            ## start lane changing
            self.lc_status = lc_op
            sx = self._waypoint_buffer[0][0]
            sy = self._waypoint_buffer[0][1]
            sz = self._waypoint_buffer[0][2]
            syaw = cal_yaw_rad(sx, sy, self._waypoint_buffer[1][0], self._waypoint_buffer[1][1])
            sv = math.sqrt(self.vehicle_state['vx']**2+self.vehicle_state['vy']**2)
            ## speed limit for lane changing
            if sv>10.0:
                sv = 10.0
            sa = 0
            target_waypoint = [self._waypoint_buffer[-1][0], self._waypoint_buffer[-1][1],self._waypoint_buffer[-1][2]]
            if lc_op == 1:
                # change right
                if self._map.query_right_lane(target_waypoint) is not None:
                    self._waypoint_buffer[-1] = self._map.query_right_lane(target_waypoint)
                else:
                    print("No candidiate right lane for waypt:"+str(target_waypoint)+"  Returned")
                    self._waypoint_buffer = []
                    return
            elif lc_op ==-1:
                # change left
                if self._map.query_left_lane(target_waypoint) is not None:
                    self._waypoint_buffer[-1] = self._map.query_left_lane(target_waypoint)
                else:
                    print("No candidiate left lane for waypt:"+str(target_waypoint)+"  Returned")
                    self._waypoint_buffer = []
                    return
            else:
                print("lc op KeyError, returned")
                return
            gx = self._waypoint_buffer[len(self._waypoint_buffer)-1][0]
            gy = self._waypoint_buffer[len(self._waypoint_buffer)-1][1]
            gz = self._waypoint_buffer[len(self._waypoint_buffer)-1][2]
            gv = sv
            gyaw = cal_yaw_rad(self._waypoint_buffer[-2][0],self._waypoint_buffer[-2][1],target_waypoint[0],target_waypoint[1])
            ga = 0
            time, x, y, yaw, v, a, j = quintic_polynomials_planner(sx, sy, syaw, sv, sa, gx, gy, gyaw, gv, ga, max_accel, max_jerk, dt)
            self._waypoint_buffer = deque(maxlen=100000)
            self._speed_profile = deque(maxlen=100000)
            for xi, yi, vi in zip(x, y, v):
                lc_pcc_v = self.pcc_reader.qurey_v(xi,yi)
                if lc_pcc_v == 0.0:
                    lc_pcc_v = 16.67
                self._speed_profile.append(lc_pcc_v)

                self._waypoint_buffer.append([xi, yi, self._map.find_z_map([xi, yi, gz])])
            self._waypoint_buffer.popleft()
            self.lc_counter = (len(x)-1)+100
            print("succ lane change plane, len"+str(len(x)))         
    
################## main entrance ######################
def main(args=None):
    rclpy.init(args=args)

    start_pt = [-252.6831285, -6325.0292965, 297.536682]
    end_pt = [-261.62358890706673, -6338.336598190479,  297.536682]

    trajectory_planner_node = TrajectoryPlanner(start_pt, end_pt)
    
    rclpy.spin(trajectory_planner_node)
    trajectory_planner_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()