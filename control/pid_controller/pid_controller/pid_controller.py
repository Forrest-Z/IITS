#!/usr/bin/env python

# Copyright (c) 2018 Intel Labs.
# authors: German Ros (german.ros@intel.com)
#
# This work is licensed under the terms of the MIT license.
# For a copy, see <https://opensource.org/licenses/MIT>.

""" This module contains PID controllers to perform lateral and longitudinal control. """

from collections import deque
import math

import numpy as np


class VehiclePIDController():
    def __init__(self, args_lateral=None, args_longitudinal=None):
        """
        :param args_lateral: dictionary of arguments to set the lateral PID controller using the following semantics:
                             K_P -- Proportional term
                             K_D -- Differential term
                             K_I -- Integral term
        :param args_longitudinal: dictionary of arguments to set the longitudinal PID controller using the following
        semantics:
                             K_P -- Proportional term
                             K_D -- Differential term
                             K_I -- Integral term
        """
        if not args_lateral:
            args_lateral = {'K_P': 3.0, 'K_D': 0.0, 'K_I': 0.001, 'dt': 0.002}
        if not args_longitudinal:
            args_longitudinal = {'K_P': 1.0,
                                 'K_D': 0.0, 'K_I': 0.001, 'dt': 0.002}

        self._lon_controller = PIDLongitudinalController(**args_longitudinal)
        self._lat_controller = PIDLateralController(**args_lateral)

    def run_step(self, target_speed, waypoint, velocity, vehicle_location, vehicle_rotation):
        """
        Execute one step of control invoking both lateral and longitudinal PID controllers to reach a target waypoint
        at a given target_speed.

        :param target_speed: desired vehicle speed
        :param waypoint: target location encoded as a waypoint
        :return: distance (in meters) to the waypoint
        """
        throttle = self._lon_controller.run_step(target_speed, velocity)
        steering = self._lat_controller.run_step(
            waypoint, vehicle_location, vehicle_rotation)

        if throttle < 0:
            brake = throttle
            throttle = 0.0
        else:
            brake = 0.0

        return steering, throttle, brake


class PIDLongitudinalController():
    """
    PIDLongitudinalController implements longitudinal control using a PID.
    """

    def __init__(self, K_P=1.0, K_D=20, K_I=0.001, dt=0.01):
        """
        :param vehicle: actor to apply to local planner logic onto
        :param K_P: Proportional term
        :param K_D: Differential term
        :param K_I: Integral term
        :param dt: time differential in seconds
        """
        self._K_P = K_P
        self._K_D = K_D
        self._K_I = K_I
        self._dt = dt
        self._e_buffer = deque(maxlen=30)
        self.long_throttle_count = 0
        self.get_throttle = AccTothrottle(
            0.8, 0.008, 0.0000256, 1.225, 7, 9000)

    def long_throttle_check(self, throttle):
        if throttle < 0.9:
            self.long_throttle_count = 0
            return False
        else:
            if self.long_throttle_count > 10:
                self.long_throttle_count = 0
                return True
            else:
                self.long_throttle_count += 1
                return False

    def run_step(self, target_speed, velocity, debug=False):
        """
        Execute one step of longitudinal control to reach a given target speed.

        :param target_speed: target speed in Km/h
        :return: throttle control in the range [0, 1]
        """
        current_speed = velocity

        if debug:
            print('Current speed = {}'.format(current_speed))

        throttle_control = self._pid_control(target_speed, current_speed)

        return throttle_control

    def _pid_control(self, target_speed, current_speed):
        """
        Estimate the throttle of the vehicle based on the PID equations

        :param target_speed:  target speed in Km/h
        :param current_speed: current speed of the vehicle in Km/h
        :return: throttle control in the range [0, 1]
        """
        _e = (target_speed - current_speed)
        self._e_buffer.append(_e)

        if len(self._e_buffer) >= 2:
            _de = (self._e_buffer[-1] - self._e_buffer[-2]) / self._dt
            _ie = sum(self._e_buffer) * self._dt
        else:
            _de = 0.0
            _ie = 0.0

        return np.clip((self._K_P * _e) + (self._K_D * _de / self._dt) + (self._K_I * _ie * self._dt), -1.0, 1.0)


class PIDLateralController():
    """
    PIDLateralController implements lateral control using a PID.
    """

    def __init__(self, K_P=1.0, K_D=0.0, K_I=0.0, dt=0.01):
        """
        :param vehicle: actor to apply to local planner logic onto
        :param K_P: Proportional term
        :param K_D: Differential term
        :param K_I: Integral term
        :param dt: time differential in seconds
        """
        self._K_P = K_P
        self._K_D = K_D
        self._K_I = K_I
        self._dt = dt
        self._e_buffer = deque(maxlen=10)

    def run_step(self, waypoint, vehicle_location, vehicle_rotation):
        """
        Execute one step of lateral control to steer the vehicle towards a certain waypoint.

        :param waypoint: target waypoint
        :return: steering control in the range [-1, 1] where:
            -1 represent maximum steering to left
            +1 maximum steering to right
        """
        return self._pid_control(waypoint, vehicle_location, vehicle_rotation)

    def _pid_control(self, waypoint, vehicle_location, vehicle_rotation):
        """
        Estimate the steering angle of the vehicle based on the PID equations

        :param waypoint: target waypoint
        :param vehicle_transform: current transform of the vehicle
        :return: steering control in the range [-1, 1]
        """

        v_begin = np.array(vehicle_location)
        v_end = v_begin + np.array([math.cos(math.radians(vehicle_rotation)),
                                    math.sin(math.radians(vehicle_rotation)), 0])
        v_vec = np.array([v_end[0] - v_begin[0], v_end[1] - v_begin[1], 0.0])
        w_vec = np.array([waypoint[0] -
                          v_begin[0], waypoint[1] -
                          v_begin[1], 0.0])
        _dot = math.acos(np.clip(np.dot(w_vec, v_vec) /
                                 (np.linalg.norm(w_vec) * np.linalg.norm(v_vec)), -1.0, 1.0))
        if np.clip(np.dot(w_vec, v_vec) /
                   (np.linalg.norm(w_vec) * np.linalg.norm(v_vec)), -1.0, 1.0) < 0.0:
            print("error! waypoint is behind ego car "+str(waypoint))

        _cross = np.cross(v_vec, w_vec)
        if _cross[2] < 0:
            _dot *= -1.0

        self._e_buffer.append(_dot)
        if len(self._e_buffer) >= 2:
            _de = (self._e_buffer[-1] - self._e_buffer[-2]) / self._dt
            _ie = sum(self._e_buffer) * self._dt
        else:
            _de = 0.0
            _ie = 0.0

        return np.clip((self._K_P * _dot) + (self._K_D * _de /
                                             self._dt) + (self._K_I * _ie * self._dt), -1.0, 1.0)

class AccTothrottle(object):
    """
    AcctoThrottle implements predicting throttle using acc
    """

    def __init__(self, cf, cr, cv, ad, A, m):
        self.cf = cf
        self.cr = cr
        self.cv = cv
        self.ad = 1.225
        self.A = A
        self.m = m
        self.g = 9.8
        self.R = 0.53
        self.tho = thr()
        self.gearpos_TransmissionRatio = dict(zip([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
                                                  [15.012, 11.667, 9.03, 7.146, 5.568, 4.375, 3.431, 2.667, 2.064, 1.663, 1.273, 1]))

    def _cal_resistance(self, v, sin_slop):

        v_kmh = v * 3.6
        friction = self.m * self.g * self.cf * sin_slop
        wind_resistance = 0.5 * self.ad * math.pow(v, 2)*self.A
        slop_resistance = self.m * self.g * sin_slop
        rolling_resistance = (self.cr + self.cv * v_kmh) * self.m * self.g

        return friction + wind_resistance + slop_resistance + rolling_resistance

    def _cal_whlend(self, v, sin_slop, acc):
        F = self._cal_resistance(v, sin_slop) + self.m * acc

        return F

    def _cal_Wheendtorque(self, v, sin_slop, acc):
        Nm = self._cal_whlend(v, sin_slop, acc) * self.R

        return Nm

    def _cal_Ngtorque(self, v, sin_slop, gear_pos, acc):
        ngtorque = self._cal_Wheendtorque(
            v, sin_slop, acc) / (self.gearpos_TransmissionRatio[gear_pos] * 2.85)

        return ngtorque

    def cal_throttle(self, v, sin_slop, gear_pos, acc, eng_speed):
        if gear_pos < 1:
            print("gear pos error "+str(gear_pos))
            gear_pos = 1.0
        throttle = self.tho.get_throttle(
            eng_speed, self._cal_Ngtorque(v, sin_slop, gear_pos, acc))
        return throttle


class thr(object):
    def __init__(self):

        self.throttle = [
            0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.85, 0.9, 0.95, 1.0
        ]

        self.rpm = [
            550.0, 718.0, 845.0, 971.0, 1097.0, 1224.0, 1350.0, 1476.0, 1603.0, 1729.0, 1813.0, 1897.0, 1982.0, 2100.0, 2150.0
        ]
        self.nm = [1.883847212, 27.13110962, 96.5399917, 176.3139327, 422.0321645, 795.5388387, 1070.658326, 1589.141496, 1967.504264, 2091.492223, 2195.915105, 2273.870037, 2315.989797, 2362.999612, 2477.999949, 2737.999902,
                   1.360376034, 25.62929403, 118.0390415, 188.8884941, 261.4890235, 660.6155153, 954.866039, 1473.429769, 1872.975136, 2034.686361, 2187.128217, 2269.496475, 2300.868346, 2354.893888, 2471.734115, 2715.052342,
                   0.018857831, 1.497981631, 73.70804668, 178.4891945, 260.2066047, 477.6227834, 767.0502697, 1276.902974, 1743.440398, 2009.176217, 2180.378941, 2267.959413, 2294.19059, 2341.271025, 2416.581509, 2468.995398,
                   0.003181718, 0.530303783, 29.88290387, 118.7716241, 248.0663284, 424.9334844, 673.8855571, 1158.218504, 1590.670897, 1924.477774, 2168.965927, 2266.549345, 2298.899416, 2335.624336, 2409.176951, 2446.183424,
                   0.001292452, 0.218694424, 14.68964257, 103.7314794, 227.406256, 367.5095544, 570.8516713, 1026.25673, 1458.434941, 1825.274015, 2125.443974, 2268.242666, 2303.496063, 2344.021725, 2395.836971, 2439.624199,
                   0.045167378, 0.342665016, 10.01671471, 62.59917279, 203.2666093, 278.6715524, 406.4771227, 844.7780191, 1287.245203, 1662.589835, 2030.432898, 2246.256657, 2302.492555, 2349.365315, 2388.045211, 2433.28465,
                   2.447095478, 5.183653412, 28.00054286, 58.04427922, 193.6434951, 249.4972974, 330.2791508, 658.0360106, 1130.272748, 1484.667071, 1883.862386, 2184.842849, 2272.978776, 2339.722573, 2384.03662, 2425.68502,
                   5.318214355, 4.791188568, 14.28768894, 36.253127, 92.61103573, 211.5357068, 279.0320513, 525.3997354, 903.7907557, 1317.017497, 1687.550149, 2050.761393, 2195.374237, 2299.802887, 2364.833323, 2407.476426,
                   0.217849151, 0.181696585, 1.958287072, 8.286180241, 18.93094062, 64.30671935, 178.0407315, 437.2103946, 605.637429, 1082.12041, 1490.412376, 1833.173502, 2007.832778, 2183.880145, 2288.411534, 2351.810536,
                   9.63e-05, 0.017139684, 1.171149387, 6.426672932, 16.12030822, 22.72242934, 58.24403698, 263.7122972, 470.6058728, 840.8171508, 1210.458741, 1630.532679, 1810.703013, 2019.76042, 2178.380839, 2273.27975,
                   8.66e-06, 0.008079381, 0.407310424, 1.445019767, 4.711384522, 10.10259235, 34.91822964, 141.4125957, 393.5208057, 711.4858769, 1054.930537, 1429.656444, 1699.080026, 1921.452621, 2081.227142, 2221.198067,
                   8.76e-07, 0.000397731, 0.016513205, 0.093963709, 1.732849366, 4.971479332, 10.16387714, 83.5300147, 314.1373125, 567.117271, 943.0088833, 1256.856264, 1539.795317, 1875.658607, 2011.00664, 2172.745346,
                   3.98e-09, 1.82e-06, 0.000104449, 0.033763055, 1.439483007, 2.258117611, 2.792851212, 58.65825008, 186.7215169, 412.3293198, 685.7146913, 1089.109185, 1246.472782, 1787.507485, 1962.724843, 2145.492134,
                   2.71e-14, 6.77e-11, 9.42e-07, 0.00080815, 0.030649282, 0.048996473, 0.038809582, 9.483992481, 26.04960503, 213.2372851, 468.5123622, 629.3338304, 775.5281646, 1138.803669, 1669.797512, 2099.394196,
                   5.16e-17, 2.5e-12, 4.76e-08, 4.05e-05, 0.001517533, 0.002501624, 0.003606977, 1.326157193, 3.625371134, 69.1194367, 272.9610734, 414.2772688, 613.5086002, 945.3602214, 1470.035611, 1910.172583]

    def _calc_coor(self, rpm, nm):
        rpm_max_index = self._binary_search(self.rpm, rpm)
        rpm_min_index = rpm_max_index - 1

        # print(self.nm[rpm_max_index*16 : (rpm_max_index+1)*16])
        nm_max_index_up = self._binary_search(
            self.nm[rpm_min_index*16: (rpm_min_index+1)*16], nm)
        nm_max_index_down = nm_max_index_up - 1

        nm_min_index_up = self._binary_search(
            self.nm[rpm_max_index*16: (rpm_max_index+1)*16], nm)
        nm_min_index_down = nm_min_index_up - 1

        return rpm_max_index, rpm_min_index, nm_max_index_up, nm_max_index_down, nm_min_index_up, nm_min_index_down

    def get_throttle(self, rpm, nm):
        rpm_max_index, rpm_min_index, nm_max_index_up, nm_max_index_down, nm_min_index_up, nm_min_index_down = self._calc_coor(
            rpm, nm)

        point1 = Point(self.rpm[rpm_max_index],
                       self.nm[rpm_max_index*16+nm_min_index_up])
        point1.set_throttle(self.throttle[nm_min_index_up])

        point2 = Point(self.rpm[rpm_max_index],
                       self.nm[rpm_max_index*16+nm_min_index_down])
        point2.set_throttle(self.throttle[nm_min_index_down])

        point3 = Point(self.rpm[rpm_min_index],
                       self.nm[rpm_min_index*16+nm_max_index_up])
        point3.set_throttle(self.throttle[nm_max_index_up])

        point4 = Point(self.rpm[rpm_min_index],
                       self.nm[rpm_min_index*16+nm_max_index_down])
        point4.set_throttle(self.throttle[nm_max_index_down])

        point5 = Point(self.rpm[rpm_min_index], nm)
        point5.throttle = (point5.nm - point4.nm)*(point3.throttle -
                                                   point4.throttle)/(point3.nm - point4.nm)+point4.throttle

        point6 = Point(self.rpm[rpm_max_index], nm)
        point6.throttle = (point6.nm - point2.nm)*(point1.throttle -
                                                   point2.throttle)/(point1.nm - point2.nm)+point2.throttle

        point = Point(rpm, nm)
        point.throttle = (rpm - point5.rpm)*(point6.throttle -
                                             point5.throttle)/(point6.rpm - point5.rpm) + point5.throttle

        return point.throttle

    def _binary_search(self, list, value):
        min = 0
        max = len(list) - 1

        while True:
            mid = int((min + max) / 2)

            if list[mid] > value:
                max = mid

            elif list[mid] < value:
                min = mid

            elif list[mid] == value:
                min = mid
                return mid
            if max - min == 1:
                return max


class Point(object):
    def __init__(self, xParam=0.0, yParam=0.0):
        self.rpm = xParam
        self.nm = yParam
        self.throttle = 0

    def __str__(self):
        return "(rpm:%.2f, nm:%.2f)" % (self.rpm, self.nm)

    def set_throttle(self, throttle):
        self.throttle = throttle
        
             


if __name__ == "__main__":
    acc = AccTothrottle(0.8, 0.008, 0.0000256, 1.225, 7, 9000)
    print(acc.cal_throttle(22, 0.01, 2, 6, 1500))
    print(acc._cal_resistance(22, 0.01))
    print(acc._cal_Ngtorque(22, 0.01, 2, 5))

    print(acc.cal_throttle(22, 0.01, 8, 3, 1500))
