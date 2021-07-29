#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
import math
import numpy as np

class CoordConverter(object):
    def __init__(self, orix, oriy, oriz, yaw):
        self.orix = orix
        self.oriy = oriy
        self.oriz = oriz
        self.yaw = yaw
        self.cosyaw = math.cos(math.pi*(self.yaw/180))
        self.sinyaw = math.sin(math.pi*(self.yaw/180)) 
        self.tranform_matrix = np.array([[self.cosyaw, self.sinyaw],[self.sinyaw, -self.cosyaw]])
        self.inverse_transform = np.linalg.inv(self.tranform_matrix)
    
    def transform_to_new(self, x ,y, z):
        xy = np.dot(self.tranform_matrix, np.array([[x-self.orix],[y-self.oriy]]))
        return [xy[0,0], xy[1,0], z-self.oriz]

    def transform_to_back(self, x, y, z):
        xy = np.dot(self.inverse_transform, np.array([[x],[y]]))
        return [xy[0,0]+self.orix, xy[1,0]+self.oriy, z+self.oriz]

    def tranform_vel_to_new(self, vx, vy, vz):
        xy = np.dot(self.tranform_matrix, np.array([[vx],[vy]]))
        return [xy[0,0], xy[1,0], vz]

    def tranform_vel_to_back(self, vx, vy, vz):
        xy = np.dot(self.inverse_transform, np.array([[vx],[vy]]))
        return [xy[0,0], xy[1,0], vz]


if __name__ == "__main__":
    coord = CoordConverter(1,1,0,30)
    a = coord.transform_to_back(0,0,0)
    print(a)