#ifndef MOTOR_H
#define MOTOR_H

class Motor {
  private:
    int pwmPin; // PWM pin for speed control
    int forwardPin; // Direction pin 1
    int backwardPin; // Direction pin 2
    int encoderPinA; // Encoder input pin
    int encoderPinB;

  public:
    Motor(int pwm, int forwardPin, int backwardPin, int encoderA, int encoderB);

    void setMotorSpeed(int speed);

    int readEncoder();
};

#endif