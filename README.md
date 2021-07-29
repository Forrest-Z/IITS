# Inceptio Intelligent Truck System

An Intelligent Self-driving Truck System For Highway Transportation

## Note
The code is still in development.

## OS requirement
Ubuntu Bionic (18.04 LTS)

## Install ROS 2 (Eloquent Elusor)

Please refer to https://index.ros.org/doc/ros2/Installation/Eloquent/Linux-Install-Debians/

### Setup Locale
```
sudo apt install -y locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8
```

### Setup Sources
``` 
sudo apt update && sudo apt install curl gnupg2 lsb-release
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -

sudo sh -c 'echo "deb [arch=$(dpkg --print-architecture)] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" > /etc/apt/sources.list.d/ros2-latest.list'
```

### Install ROS 2 packages
```
sudo apt update

sudo apt install ros-eloquent-desktop
```

### Environment setup
Add the following line into your ~/.bashrc
```
source /opt/ros/eloquent/setup.bash
```
then
```
source ~/.bashrc
```
Install argcomplete (optional but recommanded)
```
sudo apt install -y python3-pip
pip3 install -U argcomplete
```

### Install colcon
Please refer to https://index.ros.org/doc/ros2/Tutorials/Colcon-Tutorial/
```
sudo apt install python3-colcon-common-extensions
```
## Install ad_map_access
Please refer to https://ad-map-access.readthedocs.io/en/latest/BUILDING/
```
sudo apt-get install libboost-all-dev libpugixml-dev libproj-dev libgtest-dev libpython-dev libosmium2-dev liblapacke-dev libyaml-cpp-dev castxml

sudo apt install -y python-pip

pip install --user pygccxml pyplusplus xmlrunner
```

##  Create workspace

### Setup folder structure
```
mkdir -p ~/code/iits/iits_ws
cd ~/code/iits/iits_ws
```

### Get the code

```
git clone https://github.com/InceptioResearch/IITS.git
```

### Setup build environment
Perform a trival build first, this step generate build, install and log directories in the workspace.
```
colcon build --packages-select
```
Add the following line into your ~/.bashrc
```
source ~/code/iits/iits_ws/install/setup.bash
```
then
```
source ~/.bashrc
```
### Build
```
cd ~/code/iits/iits_ws/

colcon build
```

## Install Carla (Optional)
Carla is used in the visualization node
Please refer to https://carla.readthedocs.io/en/latest/start_quickstart/#carla-installation


## Install rosbag2 (Optional)
```
sudo apt-get install ros-eloquent-ros2bag ros-eloquent-rosbag2-storage-default-plugins
```
To record planner related topics
```
./src/scripts/record.sh
```
To record planner related debug topics (without planning results)
```
./src/scripts/record_debug.sh
```
To playback the recorded rosbag
```
ros2 bag play <rosbag_directory>
```

## Quick start

#### run planning with truck sim
```
ts-lm-cli
./src/scripts/start_trucksim.sh
```

#### run scenario
```
ros2 launch scenario_runner run_jinan.py
```

#### run carla bridge
```
cd /to/your/carla/folder
./CarlaUE4.sh
ros2 run carla_bridge run_carla_bridge
```

#### run trucksim bridge (please make sure that you have installed trucksim on you computer)
```
ts-lm-cli
ros2 run trucksim_bridge trucksim_bridge_node
```

