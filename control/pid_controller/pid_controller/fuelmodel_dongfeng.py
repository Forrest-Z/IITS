#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
import math
from scipy import interpolate
import numpy as np
import collections

class FuelModel(object):
    def __init__(self, time_period):
        self.time_period = time_period
        self.speed_queue = collections.deque(maxlen = 6000)
        self.fuel_queue = collections.deque(maxlen = 6000)

        self.bsfc = np.array([203.0,200.2,196.5,195.8,195.9,198.0,201.9,210.3,230.3,294.4,431.6,199.0,196.7,192.5,191.5,191.7,193.1,197.2,204.4,222.5,279.7,400.9,197.4,193.7,
                            189.3,187.9,187.8,188.9,192.6,199.3,215.0,265.8,372.6,197.4,190.9,186.9,185.6,185.4,186.8,189.4,195.8,209.5,254.8,351.7,195.0,189.9,185.8,184.6,184.2,185.5,187.6,193.5,205.3,245.8,333.3,188.5,186.3,
                            184.3,183.6,183.9,184.7,186.9,191.9,202.5,240.8,322.8,185.7,184.1,183.6,183.4,183.9,184.8,187.0,191.3,201.1,236.3,309.9,185.6,184.4,184.3,184.5,184.9,185.7,187.3,190.7,199.5,
                            231.6,303.1,187.4,186.5,186.6,187.0,187.3,187.3,188.1,190.6,198.4,228.9,294.4,192.1,191.0,190.6,190.0,189.7,189.3,189.4,191.7,200.4,232.2,300.4,198.9,196.2,194.1,192.9,192.0,
                            191.2,191.7,195.4,205.8,241.9,318.7,202.1,197.5,196.3,194.4,193.2,193.2,194.9,200.1,213.5,258.7,352.7])
        self.rpm = np.array([1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1700,1700,1700,1700,1700,1700,1700,1700,1700,1700,1700,1600,1600,1600,1600,1600,1600,
                            1600,1600,1600,1600,1600,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1400,1400,1400,1400,1400,1400,1400,1400,1400,1400,1400,1300,1300,1300,1300,1300,1300,1300,1300,1300,1300,1300,
                            1200,1200,1200,1200,1200,1200,1200,1200,1200,1200,1200,1100,1100,1100,1100,1100,1100,1100,1100,1100,1100,1100,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,900,900,900,900,900,
                            900,900,900,900,900,900,800,800,800,800,800,800,800,800,800,800,800,700,700,700,700,700,700,700,700,700,700,700,])
        self.torque = np.array([2217.0,2106.0,1873.1,1638.4,1405.7,1169.9,936.2,702.3,467.9,234.1,117.0,2348.0,2215.1,1969.0,1722.6,1477.2,1229.4,983.9,737.5,492.0,245.9,122.3,2494.0,2327.8,2068.8,1810.4,1552.7,1292.5,1034.3,775.4,517.0,258.7,129.2,2650.0,2401.2,2135.3,
                                1867.6,1600.7,1333.9,1067.3,800.8,533.4,266.8,133.4,2650.0,2476.3,2199.9,1924.8,1650.0,1375.3,1100.2,825.2,550.5,275.4,138.1,2650.0,2475.1,2200.4,1925.7,
                                1650.3,1375.0,1100.2,825.5,550.8,275.4,137.6,2650.0,2474.6,2199.5,1925.8,1649.5,1376.1,1100.1,825.2,550.3,275.2,140.3,2650.0,2473.8,2198.9,1924.2,1649.5,1374.7,1100.3,825.6,550.1,277.4,138.3,2650.0,2474.3,2199.0,1924.4,1650.9,1375.4,1101.0,
                                827.2,552.2,276.0,138.4,2501.3,2249.6,1999.8,1751.0,1500.4,1250.5,1002.2,752.0,501.1,251.7,126.5,2112.3,1890.1,1680.2,1470.0,1260.8,1052.2,841.8,631.2,419.3,210.9,106.0,1676.6,1503.3,1336.9,1169.8,1002.5,835.3,667.8,501.8,334.1,168.3,84.6])        
        self.fc = interpolate.interp2d(self.torque, self.rpm, self.bsfc, kind='cubic')
        self.total_fuel = 0
        self.total_metric = 0


    def reset_total_fuel(self):
        self.total_fuel = 0

    def calc_fuel(self, torque, rpm): 

        pe = (torque*rpm)/9550

        fuel_rate = self.fc(np.array(torque),np.array(rpm))
        self.total_fuel += (fuel_rate[0]*self.time_period*pe)/3600
        
        return self.total_fuel, fuel_rate[0]

    def get_benefit(self, speed):
        a = 1.137e-07
        b = - 3.713e-05
        c =  0.003682
        d = - 0.09686
        e =  0.7367
        return a * math.pow(speed ,4) + b * math.pow(speed, 3) + c * math.pow(speed, 2) + d * speed + e
    
    def _get_efficient(self, speed):
        a = 3.89757302e-08
        b = -1.20874469e-05
        c = 1.16866002e-03
        d = -2.70072379e-02
        e = 1.84650350e-01
        return a * math.pow(speed ,4) + b * math.pow(speed, 3) + c * math.pow(speed, 2) + d * speed + e
    
    def _get_averagespeed(self,speed):
        self.speed_queue.append(speed)
        speed_size = len(self.speed_queue)
        sum_speed = sum(self.speed_queue)

        return sum_speed / speed_size


    def _get_averagefuel(self,fuel):
        self.fuel_queue.append(fuel)
        fuel_size = len(self.fuel_queue)
        sum_fuel = sum(self.fuel_queue)

        return sum_fuel / fuel_size

    def calc_metric(self, torque, rpm, speed):
        rpm = np.clip(rpm, 600, 2150)
        pe = (torque*rpm)/9550

        fuel_rate = self.fc(np.array(torque),np.array(rpm))
        self.total_fuel += (fuel_rate[0]*self.time_period*pe)/3600
        
        average_speed = self._get_averagespeed(speed)
        average_fuel = self._get_averagefuel(fuel_rate[0])

        self.efficient = self._get_efficient(average_speed*3.6)

        if average_fuel == 0.0:
            self.benefit = 0.0
        else:
            self.benefit = (self.efficient*400) / average_fuel

        return self.total_fuel, fuel_rate[0], self.benefit

if __name__ == "__main__":
    fuelmodel = FuelModel(0.01)
    for i in range(600):
        print(fuelmodel.calc_metric(1333.9, 600.0, 20))