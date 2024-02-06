# RONA (English)

## Introduction
This repository contains the project of an omnidirectional robot with 3D printed Mecanum wheels. The goal is to achieve autonomous navigation using sensors such as LIDAR, IMU, and encoders. In the future, the plan is to add a camera and some actuators to perform tasks autonomously.

## RONA
In this section, you will find packages related to the development of an Autonomous Omnidirectional Navigation Robot (RONA). The idea is to create a physical robot that can perform autonomous navigation using a LIDAR. At the moment, I am focusing on learning how to program simulations and simulating the robot in Gazebo.

### rona_robot
This is the main package for modeling RONA. The Gazebo simulation is already functional with a LIDAR sensor, and the robot can be moved using the keyboard or an Xbox controller (with direct kinematics control). Code for navigation and sensor data collection, which I do not yet have, is yet to be developed.

To run the keyboard control use this command:
`ros2 launch rona_robot complete_gazebo.launch.py`
and
`ros2 run teleop_twist_keyboard teleop_twist_keyboard`

To run the Xbox controller control use this command:
`ros2 launch rona_robot xbox_complete_gazebo.launch.py`

### rona_controller
This package is primarily used for configuring controllers and spawning them.

### rona_communication
This package contains these nodes: 
- keyboard_to_velocity.py: converts keyboard key presses into velocity commands for the robot. It transforms Twist messages from the teleop_twist_keyboard node into Float64MultiArray messages to be sent to the `/simple_velocity_controller/commands` topic, which carries velocity commands to the robot.
- xbox_controller_to_velocity.py: subscribes to the `/joy` topic and converts joy messages into velocity commands. These messages are then published into `/kinematics_controller/command` topic. The velocity commands will be of Float64MultiArray type and will have this structure: [velocity_X_axis, velocity_Y_axis, angular_velocity]. Each of them will range from -1 to 1.
- direct_kinematics_node.py: This node will subscribe to the `/kinematics_controller/command` topic and transform the velocity messages to wheel speeds. This messages NEED to be in the mentioned format [velocity_X_axis, velocity_Y_axis, angular_velocity]. Each of them will range from -1 to 1. After the transformation, the new message is published into `/simple_velocity_controller/commands` topic.

### simple_rona_robot
This package is currently not in use; it was another approach to solve the omnidirectional robot problem without going into the complexity of modeling wheels in detail. Since the first option seems to work correctly, I prefer to continue with that.

## TODO
- DONE: Rewrite the arduino code with a class for the motor with all the relevant functions. Make it reusable and don't repeat code.
- DONE: Change the code so that it runs in two separate Arduino (due to interruption pins limitations).
- Test the motors. Run them with a pontentiometer and check if the encoders logic is working correctly.
- Think about if I should send to the arduino anithing more than the velocities. Is it worthit to make it a server-lient relation? This would mean I can send the arduino a request and it sends me back whatever I request. This may be interesing for the IMU and other future sensors, but I am no sure if it will affect the behaviour of the motors.
- *Consider the option of connecting the sensors directly to the OrangePi and let the Arduinos just manage the motors and the encoders, being the OrangePi in charge of actuating the motors depending on the information from the sensors. This would be the strongest option in my opinion.*
- Prepare the ROS2 communication code with the arduino to send velocities or whatever needed to two different serial ports.
- Prepare the ROS2 communication code to receive info from the two different Arduino. Maybe I can filter the entering messages with letters at the beggining.
- Prepare the voltage regulator to output 12 V for the motors.
- Test the communication between the OrangePi and the arduino. Maybe using the IMU (?
- Program the SLAM part of the code
- Build the actual robot,
- Maybe add some sensors when possible.

# RONA (Español)

## Introducción
Este repositorio contiene el proyecto de un robot omnidireccional con ruedas mecanum impresas en 3D. La idea es conseguir realizar navegación autónoma mediante sensores como LIDAR, IMU y encoders. En un futuro la idea es añadir alguna cámara y algún actuador para realizar tareas de forma autónoma.

## RONA
En esta sección se encuentran los paquetes relacionados con el desarrollo de un Robot Omnidireccional de Navegación Autónoma (RONA). La idea es crear un robot físico que, mediante un LIDAR, pueda realizar navegación autónoma. Por el momento, me estoy limitando a aprender a programar simulaciones y a simular el robot en Gazebo.

### rona_robot
Este es el paquete principal para el modelado de RONA. La simulación en Gazebo ya es funcional con un sensor LIDAR, y el robot se puede mover utilizando el teclado o un control de Xbox (con control de cinemática directa). Falta desarrollar código para la navegación y la recolección de datos de sensores que aún no tengo.

Para ejecutar el control con el teclado, utiliza este comando:
`ros2 launch rona_robot complete_gazebo.launch.py`
y
`ros2 run teleop_twist_keyboard teleop_twist_keyboard`

Para ejecutar el control con el controlador de Xbox, utiliza este comando:
`ros2 launch rona_robot xbox_complete_gazebo.launch.py`

### rona_controller
Este paquete se utiliza principalmente para configurar controladores y spawnearlos.

### rona_communication
Este paquete contiene estos nodos:
- `keyboard_to_velocity.py`: convierte las pulsaciones de teclas del teclado en comandos de velocidad para el robot. Transforma mensajes Twist del nodo `teleop_twist_keyboard` en mensajes `Float64MultiArray` para enviar al tema `/simple_velocity_controller/commands`, que lleva comandos de velocidad al robot.
- `xbox_controller_to_velocity.py`: se suscribe al tema `/joy` y convierte los mensajes joy en comandos de velocidad. Estos mensajes se publican en el tema `/kinematics_controller/command`. Los comandos de velocidad serán del tipo `Float64MultiArray` y tendrán esta estructura: [velocidad_eje_X, velocidad_eje_Y, velocidad_angular]. Cada uno variará de -1 a 1.
- `direct_kinematics_node.py`: este nodo se suscribe al tema `/kinematics_controller/command` y transforma los mensajes de velocidad en velocidades de rueda. Estos mensajes DEBEN estar en el formato mencionado [velocidad_eje_X, velocidad_eje_Y, velocidad_angular]. Cada uno variará de -1 a 1. Después de la transformación, el nuevo mensaje se publica en el tema `/simple_velocity_controller/commands`.

### simple_rona_robot
Este paquete no se está utilizando actualmente; era otro enfoque para resolver el problema del robot omnidireccional sin entrar en la complejidad de modelar las ruedas en detalle. Dado que la primera opción parece funcionar correctamente, prefiero continuar con esa.




