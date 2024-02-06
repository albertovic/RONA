#include "PIDController.h"

PIDController::PIDController(double p, double i, double d) : kp(p), ki(i), kd(d), setpoint(0), integral(0), lastError(0) {}

void PIDController::setSetpoint(double sp) {
    setpoint = sp;
    Serial.println("Inside setSetpoint function.");
}

double PIDController::compute(double realValue) {
    unsigned long currentTime = millis(); // Get current time
    double elapsedTime = (currentTime - lastTime); // Convert to seconds

    // 
    double error = setpoint - realValue;
    integral += error * elapsedTime;

    // Anti-windup - limit the integral term
    if (integral > 255.0 / ki) {
        integral = 255.0 / ki;
    } else if (integral < -255.0 / ki) {
        integral = -255.0 / ki;
    }

    double derivative = (error - lastError) / elapsedTime;
    lastError = error;

    // Calculate PID output
    double output = kp * error + ki * integral + kd * derivative;

    // Limit the output to the valid PWM range (0 to 255)
    if (output > 255) {
        output = 255;
    } else if (output < -255) {
        output = -255;
    }

    lastTime = currentTime; // Update last computation time
    return output;

}

void PIDController::reset() {
    integral = 0;
    lastError = 0;
}