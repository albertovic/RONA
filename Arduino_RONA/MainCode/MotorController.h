#ifndef MotorController_h
#define MotorController_h

//This class is in charge of adding up to 4 motors to a list and updating their velocities using a PID controller.
//The motors should be an already created object, this class just adds them to a list.

#include "Motor.h"
#include "PIDController.h"
#include "EncoderValues.h"
#include "Vector.h"

class MotorController {
public:
    Vector<Motor> motors;
    Vector<EncoderValues> encoderValues;
    PIDController pidController; // A single PID controller shared by all the motors
    MotorController(double kp, double ki, double kd);
    void addMotor(const Motor& motor);
    void addEncoderValue(const EncoderValues& enc);
    void setMotorSpeed(double speed);
    void updateMotorSpeeds(double speeds[2]);
    double computePID(double input);
    void setPIDSetPoint(double setPoint);
};

#endif
