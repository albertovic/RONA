#include "EncoderValues.h"

EncoderValues::EncoderValues(){}

// Returns the wheel speed in rpm
int EncoderValues::wheelSpeed(){
  double rpm = ( encoderValue1 - encoderValue2 ) / ( REDUCTION_RATIO * ( (timeStamp1 - timeStamp2) / 60000 ) );

  return map(int(rpm), -MAX_MOTOR_RPM, MAX_MOTOR_RPM, -255, 255);
}

void EncoderValues::getValue(long enc){
  encoderValue2 = encoderValue1;
  encoderValue1 = enc;

  timeStamp2 = timeStamp1;
  timeStamp1 = millis();
}