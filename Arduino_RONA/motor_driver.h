/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  #define FRONT_LEFT_MOTOR_BACKWARD 1
  #define FRONT_RIGHT_MOTOR_BACKWARD  2
  #define FRONT_LEFT_MOTOR_FORWARD  3
  #define FRONT_RIGHT_MOTOR_FORWARD   4
  #define FRONT_LEFT_MOTOR_ENABLE 22
  #define FRONT_RIGHT_MOTOR_ENABLE 23
  
  #define REAR_LEFT_MOTOR_BACKWARD 5
  #define REAR_RIGHT_MOTOR_BACKWARD  6
  #define REAR_LEFT_MOTOR_FORWARD  7
  #define REAR_RIGHT_MOTOR_FORWARD   8
  #define REAR_LEFT_MOTOR_ENABLE 24
  #define REAR_RIGHT_MOTOR_ENABLE 25
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int frontLeftSpeed, int frontRightSpeed, int rearLeftSpeed, int rearRightSpeed);
