#!/bin/sh

#cwd = $(dirname "$0")

export PYTHONPATH=''
export LD_LIBRARY_PATH=''

export FEAD_ROOT=/home/pei/work/fead/fead_ws/install

source /opt/ros/eloquent/setup.bash
source $FEAD_ROOT/setup.bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$FEAD_ROOT/planning_vip/lib/planning_vip:$FEAD_ROOT/ad_map_server/lib/ad_map_server:$FEAD_ROOT/../src/third_party/qpOASES/libs:$FEAD_ROOT/../src/third_party/osqp/libs

#export PYTHONPATH=$PYTHONPATH:$FEAD_ROOT/ad_map_access/lib:/home/dawei/fead_ws/install/ad_physics/lib:/home/dawei/Desktop/carla/carla099/PythonAPI/carla/dist/carla-0.9.9-py3.7-linux-x86_64.egg
