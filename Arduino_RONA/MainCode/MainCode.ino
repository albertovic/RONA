#include "PIDController.h"
#include "motor.h"
#include "motors_controller.h"
#include "motor_pins.h"

const unsigned long sampleTime = 20;  // Sample time in miliseconds

unsigned long lastComputeTime = 0;

Motor front_left_motor = Motor(FRONT_LEFT_MOTOR_PWM, FRONT_LEFT_MOTOR_FORWARD, FRONT_LEFT_MOTOR_BACKWARD, 0);
Motor front_right_motor = Motor(FRONT_RIGHT_MOTOR_PWM, FRONT_RIGHT_MOTOR_FORWARD, FRONT_RIGHT_MOTOR_BACKWARD, 0);
Motor rear_right_motor = Motor(REAR_RIGHT_MOTOR_PWM, REAR_RIGHT_MOTOR_FORWARD, REAR_RIGHT_MOTOR_BACKWARD, 0);
Motor rear_left_motor = Motor(REAR_LEFT_MOTOR_PWM, REAR_LEFT_MOTOR_FORWARD, REAR_LEFT_MOTOR_BACKWARD, 0);

int kp = 0;
int ki = 0;
int kd = 0;
int input = 0;

MotorController controller = MotorController(kp, ki, kd);

void setup() {
  controller.addMotor(front_left_motor);
  controller.addMotor(front_right_motor);
  controller.addMotor(rear_right_motor);
  controller.addMotor(rear_left_motor); 
}

void loop() {
  unsigned long currentTime = millis();
  double wheel_speeds[4];

  // TODO SERIAL COMMUNICATION

  // Verify if the sample time has passed
  if (currentTime - lastComputeTime >= sampleTime) {

    //Update the 4 motor speeds
    controller.updateMotorSpeeds(wheel_speeds);
    
    // Update reference time
    lastComputeTime = millis();
  }

}
