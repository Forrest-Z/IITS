from setuptools import setup, find_packages
from glob import glob

package_name = 'pid_controller'

setup(
    name=package_name,
    version='0.0.1',
    packages=find_packages(),
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
    maintainer='Lex Li',
    maintainer_email='wei.li@inceptioglobal.ai',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'run_control = pid_controller.control:main',
            'run_tick_vip_control = pid_controller.tick_vip_control_node:main'
        ],
    },
)
