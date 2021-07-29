from setuptools import setup, find_packages
from glob import glob

package_name = 'traffic_sim'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name + '/trafficData_mapped_angle/twoLanes/Fast/sample1_selected_10km',
         glob('resource/trafficData_mapped_angle/twoLanes/Fast/sample1_selected_10km/*')),
        ('share/' + package_name + '/trafficData_mapped_angle/twoLanes/constantDistance/sample4',
         glob('resource/trafficData_mapped_angle/twoLanes/constantDistance/sample4/*')),
        ('share/' + package_name, ['package.xml']),
        # Include all launch files. This is the most important line here!
        ('share/' + package_name, glob('launch/*.py')),
        # Include all config files.
        ('share/' + package_name + '/config', glob('config/*')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Lex Li',
    maintainer_email='wei.li@inceptioglobal.ai',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'run_traffic_sim = traffic_sim.traffic_sim_node:main',
            'run_traffic_list = traffic_sim.traffic_list_node:main',
            'run_nuwa_list = traffic_sim.nuwa_list:main',
            'run_xsim = traffic_sim.Xsim_bridge:main',
            'run_ego_xsim = traffic_sim.Xsim_ego_bridge:main',
            # 'run_fead_traffic_sim = traffic_sim.fead_ego_bridge:main',
            'run_fead_traffic_sim = traffic_sim.fead_ego_bridge_speed_change:main',
        ],
    },
)
