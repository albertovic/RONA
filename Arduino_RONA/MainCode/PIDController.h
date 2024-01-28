#ifndef PID_h
#define PID_h

class PIDController {
    double kp; // Proportional gain
    double ki; // Integral gain
    double kd; // Derivative gain

    double setpoint; // Desired setpoint
    double integral; // Integral term
    double lastError; // Previous error for computing derivative term
    double lastTime;

public:
    PIDController(double p, double i, double d);
    void setSetpoint(double sp);
    double compute(double input);
    void reset();
};

#endif