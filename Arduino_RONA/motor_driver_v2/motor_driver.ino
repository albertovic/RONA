/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/

#ifdef USE_BASE

#ifdef POLOLU_VNH5019
/* Include the Pololu library */
#include "DualVNH5019MotorShield.h"

/* Create the motor driver object */
DualVNH5019MotorShield drive;

/* Wrap the motor driver initialization */
void initMotorController() {
  drive.init();
}

/* Wrap the drive motor set speed function */
void setMotorSpeed(int i, int spd) {
  if (i == LEFT) drive.setM1Speed(spd);
  else drive.setM2Speed(spd);
}

// A convenience function for setting both motor speeds
void setMotorSpeeds(int frontleftSpeed, int frontrightSpeed, int rearLeftSpeed, rearRightSpeed) {
  setMotorSpeed(FRONT_LEFT, frontleftSpeed);
  setMotorSpeed(FRONT_RIGHT, frontrightSpeed);
  setMotorSpeed(REAR_LEFT, rearLeftSpeed);
  setMotorSpeed(REAR_RIGHT, rearRightSpeed);
}
#elif defined POLOLU_MC33926
/* Include the Pololu library */
#include "DualMC33926MotorShield.h"

/* Create the motor driver object */
DualMC33926MotorShield drive;

/* Wrap the motor driver initialization */
void initMotorController() {
  drive.init();
}

/* Wrap the drive motor set speed function */
void setMotorSpeed(int i, int spd) {
  if (i == LEFT) drive.setM1Speed(spd);
  else drive.setM2Speed(spd);
}

// A convenience function for setting both motor speeds
void setMotorSpeeds(int frontleftSpeed, int frontrightSpeed, int rearLeftSpeed, rearRightSpeed) {
  setMotorSpeed(FRONT_LEFT, frontleftSpeed);
  setMotorSpeed(FRONT_RIGHT, frontrightSpeed);
  setMotorSpeed(REAR_LEFT, rearLeftSpeed);
  setMotorSpeed(REAR_RIGHT, rearRightSpeed);
}
#elif defined L298_MOTOR_DRIVER
void initMotorController() {
  digitalWrite(FRONT_RIGHT_MOTOR_ENABLE, HIGH);
  digitalWrite(FRONT_LEFT_MOTOR_ENABLE, HIGH);
  digitalWrite(REAR_RIGHT_MOTOR_ENABLE);
  digitalWrite(REAR_RIGHT_MOTO_ENABLE, HIGH);
}

void setMotorSpeed(int i, int spd) {
  unsigned char reverse = 0;

  if (spd < 0) {
    spd = -spd;
    reverse = 1;
  }
  if (spd > 255)
    spd = 255;

  if (i == FRONT_LEFT) {
    if (reverse == 0) {
      analogWrite(FRONT_LEFT_MOTOR_FORWARD, spd);
      analogWrite(FRONT_LEFT_MOTOR_BACKWARD, 0);
    } else if (reverse == 1) {
      analogWrite(FRONT_LEFT_MOTOR_BACKWARD, spd);
      analogWrite(FRONT_LEFT_MOTOR_FORWARD, 0);
    }
  } else /*if (i == RIGHT) //no need for condition*/ {
    if (reverse == 0) {
      analogWrite(FRONT_RIGHT_MOTOR_FORWARD, spd);
      analogWrite(FRONT_RIGHT_MOTOR_BACKWARD, 0);
    } else if (reverse == 1) {
      analogWrite(FRONT_RIGHT_MOTOR_BACKWARD, spd);
      analogWrite(FRONT_RIGHT_MOTOR_FORWARD, 0);
    }
  }
}

void setMotorSpeeds(int leftSpeed, int rightSpeed) {
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}
#else
#error A motor driver must be selected!
#endif

#endif
