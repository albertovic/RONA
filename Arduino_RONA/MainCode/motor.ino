#include "motor.h"

Motor::Motor(int pwm, int forwardPin, int backwardPin, int encoderA, int encoderB) {
  pwmPin = pwm;
  this->forwardPin = forwardPin;
  this->backwardPin = backwardPin;
  encoderPinA = encoderA;
  encoderPinB = encoderB;

  // Initialize pin modes
  pinMode(pwmPin, OUTPUT);
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
  pinMode(encoderPin, INPUT);
}

void Motor::setMotorSpeed(int speed) {
  if (speed > 255){
    speed = 255;
  }

  if (speed > 0){
    analogWrite(forwardPin, speed);
    analogWrite(backwardPin, 0);
  }
  else if (speed < 0){
    speed = -speed;
    analogWrite(forwardPin, 0);
    analogWrite(backwardPin, speed);
  }
}

int Motor::readEncoder() {
  // Implement encoder reading logic here
  // Return the encoder value
}