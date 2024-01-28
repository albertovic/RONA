#include <Arduino.h>

class Motor {
  private:
    int pwmPin; // PWM pin for speed control
    int directionPin1; // Direction pin 1
    int directionPin2; // Direction pin 2
    int encoderPin; // Encoder input pin

  public:
    Motor(int pwm, int forwardPin, int backwardPin, int encPin) {
      pwmPin = pwm;
      forwardPin = forwardPin;
      backwardPin = backwardPin;
      encoderPin = encPin;

      // Initialize pin modes
      pinMode(pwmPin, OUTPUT);
      pinMode(directionPin1, OUTPUT);
      pinMode(directionPin2, OUTPUT);
      pinMode(encoderPin, INPUT);
    }

    void SetMotorSpeed(int speed) {
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

    void rotateClockwise() {
      // Implement motor rotation logic here
    }

    void rotateCounterClockwise() {
      // Implement motor rotation logic here
    }

    void stop() {
      // Implement motor stop logic here
    }

    int readEncoder() {
      // Implement encoder reading logic here
    }
};
