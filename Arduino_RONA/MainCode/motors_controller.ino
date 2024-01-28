#include "motors_controller.h"

MotorController::MotorController(double kp, double ki, double kd)
    : pidController(kp, ki, kd) {}

void MotorController::addMotor(const Motor& motor) {
    motors.push_back(motor);
}

void MotorController::setMotorSpeed(double speed) {
    pidController.setSetpoint(speed);
}

void MotorController::updateMotorSpeeds(double speeds[4]) {
    for (size_t i = 0; i < motors.size(); ++i) {
        pidController.setSetpoint(speeds[i]);
        int encoderValue = motors[i].readEncoder();
        double output = pidController.compute(encoderValue);
        motors[i].setMotorSpeed(output);
    }
}

double MotorController::computePID(double input){
  return pidController.compute(input);
}
