#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
# ### offline pcc
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
# from pykdtree.kdtree import KDTree
from scipy.spatial import cKDTree as KDTree

try:
    #### for debug ######
    from HDMap import HDmap
    from pcc.main import PCC_algorithm
    from coord_tranform import Coord_Trans
except:
    ##### for release #####
    from trajectory_planner.pcc.main import PCC_algorithm
    from trajectory_planner.HDMap import HDmap
    from trajectory_planner.coord_tranform import Coord_Trans

from ad_map_server_py.ad_map_server import CoordTrans
from ament_index_python.packages import get_package_share_directory
package_share_directory = get_package_share_directory('trajectory_planner')

class OfflinePCC(Node):
    # add some contraint here
    def __init__(self, start_point, end_point):
        super().__init__('offline_pcc')
        self._map = HDmap()

        self.pcc_file_dir = os.path.join(package_share_directory, "offline_pcc.txt")
        self.global_plan_dir = os.path.join(package_share_directory, "global_routing.txt")

        ## trucksim coord start and end
        self.coord_trans = CoordTrans(-225.151904, -6337.384475)
        self.start_point = self.coord_trans.trucksim_to_map(start_point[0], start_point[1]) +[start_point[2]]
        self.end_point = self.coord_trans.trucksim_to_map(end_point[0], end_point[1]) + [end_point[2]]
        ## map coord 

        self._global_plan = self._map.GlobalPlanner_waypoints(self.start_point, self.end_point)
        self._speed_profile = deque(maxlen=1000000000000000000)
        self._x = deque(maxlen=1000000000000000000)
        self.speed_planner = PCC_algorithm()
        self.grad_x = None
        self.grad = None

        ## reference/target speed for pcc
        self.target_speed = 16.67
    
    def pcc_peak_adjust(self, pcc_x, pcc_v, grad_x, grad):
        def find_peak(array_like):
            peak_indexs_up = []
            peak_indexs_down = []
            peak_indexs = []
            direction_signal = 0
            for i in range(len(array_like)-1):
                #down peak
                if array_like[i]<array_like[i+1]:
                    if direction_signal != 1:
                        peak_indexs_down.append(i)
                        peak_indexs.append(i)
                        direction_signal = 1
                ##high peak
                elif array_like[i]>array_like[i-1]:
                    if direction_signal != -1:
                        peak_indexs_up.append(i)
                        peak_indexs.append(i)
                        direction_signal = -1
                else:
                    pass
            return peak_indexs_up, peak_indexs_down, peak_indexs
        
        pcc_v_peaks_up, pcc_v_peaks_down, pcc_v_peaks = find_peak(pcc_v)
        grad_peaks_up, grad_peaks_down, grad_peaks = find_peak(grad)

        def find_nearest_pcc_peak(peaks_list, peak):
            dist = 10000
            candidiate_idx = 0
            for i in range(len(peaks_list)):
                if dist>(peaks_list[i]-peak)**2:
                    dist = (peaks_list[i]-peak)**2
                    candidiate_idx = i
            return candidiate_idx

        previous_pcc_peak_idx = 0
        for i in range(0, len(grad_peaks)):
            ## find nearest pcc peak comparing to grad peak
            choosen_pcc_peaks = pcc_v_peaks_up
            for itm in grad_peaks_up:
                if grad_peaks[i] == itm:
                    choosen_pcc_peaks = pcc_v_peaks_down
                    break
            this_pcc_peak_idx = find_nearest_pcc_peak(choosen_pcc_peaks, grad_peaks[i])
            for j in range(len(pcc_v_peaks)):
                if pcc_v_peaks[j] == choosen_pcc_peaks[this_pcc_peak_idx]:
                    this_pcc_peak_idx = j
                    break
            leng_old = pcc_x[pcc_v_peaks[this_pcc_peak_idx]]-pcc_x[pcc_v_peaks[previous_pcc_peak_idx]]
            leng_new = grad_x[grad_peaks[i]]-pcc_x[pcc_v_peaks[previous_pcc_peak_idx]]
            this_peak_offset = grad_x[grad_peaks[i]] - pcc_x[pcc_v_peaks[this_pcc_peak_idx]]
            pcc_x[pcc_v_peaks[this_pcc_peak_idx]] = grad_x[grad_peaks[i]]
            for idx in range(pcc_v_peaks[previous_pcc_peak_idx]+1, pcc_v_peaks[this_pcc_peak_idx]):
                pcc_x[idx] = leng_new*(pcc_x[idx]-pcc_x[pcc_v_peaks[previous_pcc_peak_idx]])/leng_old + pcc_x[pcc_v_peaks[previous_pcc_peak_idx]]
            for idxp in range(pcc_v_peaks[this_pcc_peak_idx]+1, len(pcc_x)):
                pcc_x[idxp] = pcc_x[idxp]+this_peak_offset
            previous_pcc_peak_idx = this_pcc_peak_idx
        return pcc_x, pcc_v

                
    def compute_speed_profile(self):
        def compute_distance(loc1, loc2):
            return math.sqrt((loc1[0]-loc2[0])**2+(loc1[1]-loc2[1])**2)
        grad_x, grad = self._map.query_gradient(self._global_plan)
        self.grad_x = grad_x
        self.grad = grad
        step_size = 10000
        grad_x_step = np.array(grad_x[::step_size])
        grad_step = grad[::step_size]
        pcc_v, pcc_x = self.speed_planner.pcc_speed_planner(grad_x_step.tolist(), grad_step, self.target_speed)
        pcc_x, pcc_v = self.pcc_peak_adjust(pcc_x, pcc_v, grad_x_step, grad_step)
        for v, x in zip(pcc_v, pcc_x):
            self._speed_profile.append(v)
            self._x.append(x)

    def write_planning_result(self):
        with open(self.pcc_file_dir, "w") as f:
            for i in range(len(self._speed_profile)):
                write_line = str(self._x[i])+" "+str(self._speed_profile[i])+"\n"
                f.write(write_line)

    def write_global_plan(self):
        with open(self.global_plan_dir, "w") as f:
            for i in range(len(self._global_plan)):
                write_line = str(self._global_plan[i][0])+" "+str(self._global_plan[i][1])+" "+str(self._global_plan[i][2])+" "+str(self.grad_x[i])+" "+str(self.grad[i])+"\n"
                f.write(write_line)

class PCCReader(object):
    def __init__(self, pcc_file_dir = None, global_plan_dir = None):

        if pcc_file_dir == None:
            self.pcc_file_dir = os.path.join(package_share_directory, "offline_pcc.txt")
        else:
            self.pcc_file_dir = pcc_file_dir

        if global_plan_dir == None:
            self.global_plan_dir = os.path.join(package_share_directory, "global_routing.txt")
        else:
            self.global_plan_dir = global_plan_dir

        self.f = open(self.pcc_file_dir, "r")
        self.gp_f = open(self.global_plan_dir)
        self.pcc_x = []
        self.pcc_v = []
        self.global_plan=None
        self.x = []
        self.y = []
        self.z = []
        self.grad = []
        self.xp = []
        self.xy_xp = None
        self.tree = None
        self.xy_numpy = []
        self._process_file()

        
    ## no use if there is offline planned routing, use read global plan instead
    def set_global_plan(self, global_plan, xp):
        self.global_plan = global_plan
        self.xp = xp
        x = []
        y = []
        step = 1000
        for waypoint in self.global_plan:
            x.append(waypoint[0])
            y.append(waypoint[1])
        self.xy_xp = interpolate.interp2d(x[0:-1:step], y[0:-1:step], self.xp[0:-1:step])
    
    def read_global_plan(self):
        return self.global_plan

    def _process_file(self):
        ## offline pcc speed profile
        for line in self.f.readlines():
            processed_line = line.split( )
            self.pcc_x.append(float(processed_line[0]))
            self.pcc_v.append(float(processed_line[1]))
        self.pcc_v_f = interpolate.interp1d(self.pcc_x, self.pcc_v, kind='linear', fill_value='extrapolate')

        ## offline routing
        step = 100
        for line in self.gp_f.readlines():
            processed_line = line.split( )
            self.x.append(float(processed_line[0]))
            self.y.append(float(processed_line[1]))
            self.z.append(float(processed_line[2]))
            self.xp.append(float(processed_line[3]))
            self.xy_numpy.append([float(processed_line[0]),float(processed_line[1])])
        self.xy_numpy = np.array(self.xy_numpy[::step])
        self.xp = np.array(self.xp[::step])
        self.tree = KDTree(self.xy_numpy)


    def qurey_x(self, x, y):
        dist, ind = self.tree.query([x,y], k=1)
        return self.xp[ind]

    def qurey_v(self, x):
        return self.pcc_v_f(x)

    def plot_road_grad(self):
        x_node = self.xp
        h_node = self.z
        dx_elem = np.array([x_node[i+1] - x_node[i] for i in range(0, len(x_node)-1, 1000)])
        dh_elem = np.array([h_node[i+1] - h_node[i] for i in range(0, len(h_node)-1, 1000)])
        Ge = dh_elem/dx_elem
        x = np.array([x_node[i] for i in range(0, len(x_node)-1, 1000)])
        plt.plot(x, Ge)
        plt.show()

class PCCReader2(Node):
    def __init__(self, pcc_file_dir = None):
        super().__init__('pcc_reader')
        if pcc_file_dir == None:
            self.pcc_file_dir =  os.path.join(package_share_directory, "new_pcc_result.txt")
        else:
            self.pcc_file_dir = pcc_file_dir

        self.f = open(self.pcc_file_dir, "r")
        self.coord_trans = CoordTrans()
        self.pcc_v = []
        self.x = []
        self.y = []
        self.z = []
        self.xy_numpy = []
        self.tree = None
        
        self.v_scaling = 16.67/16.67
        
        self._process_file()

    def utm_to_enu(self, xyz):
        if len(xyz) == 3:
            return [xyz[0]-572196.963588907, xyz[1]-4026790.1365981903,xyz[2]]
        if len(xyz) == 2:
            return [xyz[0]-572196.963588907, xyz[1]-4026790.1365981903]
        

    def _process_file(self):
        ## offline pcc speed profile
        for line in self.f.readlines():
            processed_line = line.split( )
            wx, wy, wz = float(processed_line[0]),float(processed_line[1]),float(processed_line[2])
            [x, y, z] = self.utm_to_enu([wx, wy, wz])
            self.x.append(float(x))
            self.y.append(float(y))
            self.z.append(float(z))
            self.xy_numpy.append([x,y])
            self.pcc_v.append(float(processed_line[3]))
        self.xy_numpy = np.array(self.xy_numpy)
        self.tree = KDTree(self.xy_numpy)
        
    
    def qurey_v(self, x, y):
        dist, ind = self.tree.query([x,y], k=1)
        if self.pcc_v[ind] < 10:
            v = 10
        else:
            v = self.pcc_v[ind]
        return v*self.v_scaling

    def plot_pcc_result(self):
        ax = plt.gca()
        distance_list = []
        time_tick = []
        t = np.array([i for i in range(len(self.x))])
        ax.plot(t, np.array(self.z)/7)
        ax.plot(t, self.pcc_v)
        for i in range(len(self.x)-1):
            distance_list.append(math.sqrt((self.x[i]-self.x[i+1])**2+(self.y[i]-self.y[i+1])**2+(self.z[i]-self.z[i+1])**2))
            time_tick.append(distance_list[i]/(self.pcc_v[i]+1e-100))
        self.pcc_v = np.array(self.pcc_v)
    
        plt.show()
    
    def test(self, x_list, y_list, z_list):
        ax = plt.gca()
        t = np.array([i for i in range(len(x_list[::1000]))])
        ax.plot(t, (np.array(z_list[::1000])-300)/5)
        v = []
        for x, y in zip(x_list[::1000], y_list[::1000]):
            v.append(self.qurey_v(x, y))
        ax.plot(t, v)
        plt.show()


################## main entrance ######################
def main(args=None):
    rclpy.init(args=args)
    # offline_pcc_node = OfflinePCC([-229.323,-6344.25,297.901], [686.306,6672.5,408.462])
    offline_pcc_node = OfflinePCC([-170.51309600000002, 102.1044750000001, 295.313], [927.53599-2.114085999999986, 12948.4684-3.2139649999999165, 408.727])
    offline_pcc_node.compute_speed_profile()
    offline_pcc_node.write_planning_result()
    offline_pcc_node.write_global_plan()
    offline_pcc_node.destroy_node()
    rclpy.shutdown()

def test_pcc_reader(args=None):
    rclpy.init(args=args)
    pcc_reader = PCCReader2()
    pcc_reader.plot_pcc_result()
    pcc_reader_previous = PCCReader()
    pcc_reader.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    # main()
    test_pcc_reader()