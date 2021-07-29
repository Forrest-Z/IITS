#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
import os
import launch
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import EnvironmentVariable
from launch.substitutions import LaunchConfiguration
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument

def generate_launch_description():
    scenario_runner_package = 'scenario_runner'
    scenario_runner_parameter = os.path.join(get_package_share_directory(scenario_runner_package), 'config', 'settings.yaml')

    trucksim_package = 'trucksim_bridge'
    trucksim_package_dir_share = get_package_share_directory(trucksim_package)
    trucksim_parameter = os.path.join(get_package_share_directory(trucksim_package), 'config', 'settings.yaml')

    carla_package = 'carla_bridge'
    carla_package_dir_share = get_package_share_directory(carla_package)
    carla_parameter = os.path.join(get_package_share_directory(carla_package), 'config', 'settings.yaml')

    hdmap_pkg = 'ad_map_server'
    hdmap_dir = get_package_share_directory(hdmap_pkg)

    return LaunchDescription([
        Node(
            package=scenario_runner_package,
            # node_namespace='fead',
            node_executable='run_jinan',    
            node_name=scenario_runner_package,
            parameters=[scenario_runner_parameter],
            remappings=None,
            output='screen',
            emulate_tty=True,
            arguments=['--ros-args --log-level INFO']
        ), 
        Node(
            package='ad_map_server',
            # node_namespace='fead',
            node_executable='ad_map_server',    
            node_name='map_server' ,
            remappings=None,
            output='screen',
            cwd = hdmap_dir,
            emulate_tty=True,
            # arguments=['resource/jinan_config.txt']
            arguments=['resource/jinan_two_lanes_config.txt']
        ),
        Node(
            package='traffic_sim',
            # node_namespace='fead',
            node_executable='run_traffic_sim',    
            node_name='traffic_sim' ,
            remappings=None,
            output='screen',
            emulate_tty=True,
            arguments=['--ros-args --log-level INFO']
        ),
        Node(
            package='traffic_sim',
            # node_namespace='fead',
            node_executable='run_traffic_list',    
            node_name='traffic_sim' ,
            remappings=None,
            output='screen',
            emulate_tty=True,
            arguments=['--ros-args --log-level INFO']
        ),
        Node(
            package='trajectory_planner',
            # node_namespace='fead',
            node_executable='run_trajectory_planner',    
            node_name='trajectory_planner' ,
            remappings=None,
            output='screen',
            emulate_tty=True,
            arguments=['--ros-args --log-level INFO']
        ),
        Node(
            package='trajectory_planner',
            # node_namespace='fead',
            node_executable='run_greedy_dm',    
            node_name='greedy_dm' ,
            remappings=None,
            output='screen',
            emulate_tty=True,
            arguments=['--ros-args --log-level INFO']
        ),
        Node(
            package='trucksim_bridge',
            # node_namespace='fead',
            node_executable='trucksim_bridge_node',    
            node_name='trucksim_bridge',
            parameters=[trucksim_parameter],
            remappings=None,
            cwd = trucksim_package_dir_share,
            output='screen',
            emulate_tty=True
        ),
        Node(
            package='pid_controller',
            # node_namespace='fead',
            node_executable='run_control',    
            node_name='pid_controller' ,
            remappings=None,
            output='screen',
            emulate_tty=True,
            arguments=['--ros-args --log-level INFO']
        ),
        Node(
            package=carla_package,
            # node_namespace='fead',
            node_executable='run_carla_bridge',    
            node_name=carla_package,
            parameters=[carla_parameter],
            remappings=None,
            output='screen',
            emulate_tty=True,
            cwd = carla_package_dir_share,
            arguments=['--ros-args --log-level INFO']
        ),
    ])
