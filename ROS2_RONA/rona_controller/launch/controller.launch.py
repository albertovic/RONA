#This launch file is in charge of spawning the controller nodes that will be used 

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    
    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "joint_state_broadcaster",
            #This sets the namespace
            "--controller-manager",
            "/controller_manager"
        ]
    )

    # The velocity controller is configured in rona_controllers.yaml.
    # The spawner node is used to load controllers in time of execution.
    simple_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "simple_velocity_controller",
            "--controller-manager",
            "/controller_manager"
        ]
    )

    return LaunchDescription([
        joint_state_broadcaster_spawner,
        simple_controller_spawner
    ])