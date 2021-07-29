#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
class Coord_Trans(object):
    def __init__(self, delta_x, delta_y):
        self.delta_x = delta_x
        self.delta_y = delta_y

    def trucksim_to_map(self, x, y):
        return [x+self.delta_x, y+self.delta_y]

    def trucksim_to_carla(self, x, y):
        return [x+self.delta_x, -(y+self.delta_y)]
    
    def carla_to_map(self, x, y):
        return [x, -y]
    
    def map_to_trucksim(self, x, y):
        return [x-self.delta_x, y-self.delta_y]
    
    def map_to_carla(self, x, y):
        return [x, -y]


if __name__ == "__main__":
    x_pos = [-112.0, 76.4,296.0696]
    end_pos = [927.53599, 12948.4684, 408.727]
    map_start = [-282.034,-6311.39,297.135]
    map_end = [700.27,6607.87,408.727]
    coord_trans = Coord_Trans(-225.151904, -6337.384475)
    coord_trans = Coord_Trans(-227.26599, -6340.59844)
    print(coord_trans.map_to_trucksim(map_start[0], map_start[1]))
    print(coord_trans.map_to_trucksim(map_end[0], map_end[1]))
