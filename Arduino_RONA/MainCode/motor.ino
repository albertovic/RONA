#include "motor.h"

#define REDUCTION_RATIO 21.3

Motor::Motor(int pwm, int forwardPin, int backwardPin) {
  pwmPin = pwm;
  this->forwardPin = forwardPin;
  this->backwardPin = backwardPin;

  // Initialize pin modes
  pinMode(pwmPin, OUTPUT);
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
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

