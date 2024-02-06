#include "MotorController.h"

MotorController::MotorController(double kp, double ki, double kd)
    : pidController(kp, ki, kd) {}

void MotorController::addMotor(const Motor& motor) {
    motors.push_back(motor);
}

void MotorController::addEncoderValue(const EncoderValues& enc){
    encoderValues.push_back(enc);
}

void MotorController::setMotorSpeed(double speed) {
    pidController.setSetpoint(speed);
}

void MotorController::updateMotorSpeeds(double speeds[2]) {
    for (size_t i = 0; i < motors.size(); ++i) {
        // Sets the new speeds to the motors
        pidController.setSetpoint(speeds[i]);
        // Gets the speed of the wheel from the encoder already transformed in RPM
        int speedEncoderValue = encoderValues[i].wheelSpeed();
        // Computes the PID with the speed value from the encoders as the real value
        double output = pidController.compute(speedEncoderValue);
        // Sets the motor speeds as the computed value from the PID loop
        motors[i].setMotorSpeed(output);
    }
}

double MotorController::computePID(double input){
  return pidController.compute(input);
}
