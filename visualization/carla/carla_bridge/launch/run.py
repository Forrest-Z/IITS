import os
import launch
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import EnvironmentVariable
from launch.substitutions import LaunchConfiguration
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument

def generate_launch_description():
    package_name = 'carla_bridge'

    para_dir = os.path.join(get_package_share_directory(package_name), 'config', 'settings.yaml')
    rviz_config_dir = os.path.join(get_package_share_directory(package_name), 'config', 'default.rviz')

    return LaunchDescription([
        Node(
            package=package_name,
            node_namespace='fead',
            node_executable='run_carla_bridge',    
            node_name='carla_bridge',
            parameters=[para_dir],
            remappings=None,
            output='screen',
            emulate_tty=True,
            arguments=['--ros-args --log-level INFO']
        )
    ])