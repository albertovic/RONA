#ifndef ENC_VAL
#define ENC_VAL

#define REDUCTION_RATIO 21.3
#define MAX_MOTOR_RPM 400

class EncoderValues{

unsigned long timeStamp1 = 0;
unsigned long timeStamp2 = 0;
long encoderValue1 = 0;
long encoderValue2 = 0;

public:

  EncoderValues();

  int wheelSpeed();

  void getValue(long );
};

#endif
