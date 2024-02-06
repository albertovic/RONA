#ifndef ENC_VAL
#define ENC_VAL

#define REDUCTION_RATIO 21.3
#define MAX_MOTOR_RPM 400

class EncoderValues{

unsigned long timeStamp1 = 100;
unsigned long timeStamp2 = 200;
long encoderValue1 = 90;
long encoderValue2 = 40;

public:

  EncoderValues();

  int wheelSpeed();

  void getValue(long );
};

#endif
