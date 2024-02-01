// B Port pins
#define LEFT_ENCODER_A  PB4 //Pin 10 - PCINT4
#define LEFT_ENCODER_B  PB5 //Pin 11 - PCINT5

// D Port pins
#define RIGHT_ENCODER_A PD0 //Pin 21 - PCINT0
#define RIGHT_ENCODER_B PD1 //Pin 20 - PCINT1

   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

