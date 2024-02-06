#ifndef MOTOR_H
#define MOTOR_H

#include "encoder.h"

class Motor {
  private:
    int pwmPin; // PWM pin for speed control
    int forwardPin; // Direction pin 1
    int backwardPin; // Direction pin 2

    volatile long enc_value_1 = 0L;
    volatile long enc_value_2 = 0L;

    int wheelSpeed = 0;

  public:
    Motor(int pwm, int forwardPin, int backwardPin);

    void setMotorSpeed(int speed);

};

#endif