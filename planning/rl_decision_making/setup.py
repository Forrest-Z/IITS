#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
from setuptools import setup, find_packages
from glob import glob
package_name = 'rl_decision_making'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(),  # include all packages under src
    #package_dir={"": "src"},   # tell distutils packages are under src
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        # Include all launch files. This is the most important line here!
        ('share/' + package_name, glob('launch/*.py')),
        # Include all config files.
        ('share/' + package_name + '/config', glob('config/*')),
        # Include all resource
        ('share/' + package_name, glob('resource/*.*')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='liwei',
    maintainer_email='wei.li@inceptioglobal.ai',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'run_trainer = rl_decision_making.traffic_process_train:main',
            'run_test = rl_decision_making.rl_decision_making:main'
        ],
    },
)
