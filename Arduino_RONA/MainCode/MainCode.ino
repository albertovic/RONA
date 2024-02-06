#include "PIDController.h"
#include "Motor.h"
#include "MotorController.h"
#include "motor_pins.h"
#include "encoder.h"
#include "commands.h"

#define BAUD_RATE 9600

const unsigned long sampleTime = 20;  // Sample time in miliseconds

unsigned long lastComputeTime = 0;

// Variable for the wheel speeds
static double wheel_speeds[2];

// New set point for the PID controller
double newSetPoint;

// Values for the PID Controller
int kp = 0;
int ki = 0;
int kd = 0;
int input = 0;

// Variables to help parse the commands. Used later in the loop and the runCommand() and resetCommand() operations.
int arg = 0;
int index = 0;

// Variable to store an input character from the serial port
char chr;

// Variable to store the single-character command
char cmd;

// Char arrays that store the first and second argument of the serial command
char argv1[16];
char argv2[16];

// The variables to store the arguments in long form
long arg1;
long arg2;

// Creation of a controller object (PID)
MotorController controller = MotorController(kp, ki, kd);

// Creation of the motor objects
Motor left_motor = Motor(LEFT_MOTOR_PWM, LEFT_MOTOR_FORWARD, LEFT_MOTOR_BACKWARD);
Motor right_motor = Motor(RIGHT_MOTOR_PWM, RIGHT_MOTOR_FORWARD, RIGHT_MOTOR_BACKWARD);

EncoderValues left_enc_value = EncoderValues();
EncoderValues right_enc_value = EncoderValues();

void setup() {
  // Add the motors to the controller
  controller.addMotor(left_motor);
  controller.addMotor(right_motor);
  // Add the encoderValues to the controller. They are basically structures that storage the values from the encoders and transform them into usable data (see class)
  controller.addEncoderValue(left_enc_value);
  controller.addEncoderValue(right_enc_value);

  Serial.begin(9600);

  DDRB &= ~(1<<LEFT_ENCODER_A);
  DDRB &= ~(1<<LEFT_ENCODER_B);
  DDRD &= ~(1<<RIGHT_ENCODER_A);
  DDRD &= ~(1<<RIGHT_ENCODER_B);
    
  //enable pull up resistors
  PORTB |= (1<<LEFT_ENCODER_A);
  PORTB |= (1<<LEFT_ENCODER_B);
  PORTD |= (1<<RIGHT_ENCODER_A);
  PORTD |= (1<<RIGHT_ENCODER_B);
  
  // tell pin change mask to listen to left encoder pins
  PCMSK2 |= (1 << LEFT_ENCODER_A)|(1 << LEFT_ENCODER_B);
  // tell pin change mask to listen to right encoder pins
  PCMSK1 |= (1 << RIGHT_ENCODER_A)|(1 << RIGHT_ENCODER_B);
    
  // enable PCINT1 and PCINT2 interrupt in the general interrupt mask
  PCICR |= (1 << PCIE1) | (1 << PCIE2);
}

// The loop is in charge of the serial communication, as well as updating the wheel speeds when the time is greater than the assigned sample time
void loop() {
  //Serial.print("Printing inside loop but outside while.");

  //TESTING ZONE BEGIN


  //TESTING ZONE END

  // TODO SERIAL COMMUNICATION
  while (Serial.available()>0){

    //Serial.print("Printing inside while");

    // Read next character
    chr = Serial.read();
    //Check if chr is a carriage return (13 in ASCII), meaning the end of the command
    if(chr == 13){
      if(arg == 1)argv1[index] = NULL;
      else if(arg == 2) argv2[index] = NULL;
      runCommand();
      resetCommand();
    } else if(chr==' '){
      if(arg == 0) arg = 1;
      else if(arg == 1){
        argv1[index] = NULL;
        arg = 2;
        index = 0;
      }
      continue;
    }
    else{
      if(arg == 0){
        // The first arg is the single-letter command
        cmd = chr;
      }
      else if(arg == 1){
        argv1[index] = chr;
        index++;
      }
      else if(arg == 2){
        argv2[index] = chr;
        index++;
      }
    }
  }

  // With a switch-case use create a case that gets the SetPoint and 

  // Verify if the sample time has passed
  if (millis() - lastComputeTime >= sampleTime) {
    // Update the 4 motor speeds.
    // This command is in charge of:
    // - Sending the new speed to the motors (pidController.setSetpoint(speeds[i]);)
    // - Reading the encoder value from the encoderValues objects (int speedEncoderValue = encoderValues[i].wheelSpeed();)
    // - Computes the PID with the speed value from the encoders as the real value
    // - Sets the motor speeds as the computed value from the PID loop
    controller.updateMotorSpeeds(wheel_speeds);
    
    // Update reference time
    lastComputeTime = millis();
  }
}

void runCommand(){
  int i = 0;
  arg1 = atoi(argv1);
  arg2 = atoi(argv2);

  switch(cmd){
    case READ_ENCODERS:
      Serial.print(readEncoder(LEFT));
      Serial.print(" ");
      Serial.println(readEncoder(RIGHT));
      break;
    case RESET_ENCODERS:
      resetEncoders();
      controller.pidController.setSetpoint(0);
      Serial.println("Encoders and PID controller reset");
      break;
    case READ_MOTOR_SPEEDS:
      Serial.print(left_enc_value.wheelSpeed());
      Serial.print(" ");
      Serial.println(right_enc_value.wheelSpeed());
      break;
    case SET_MOTOR_SPEEDS:
      wheel_speeds[0] = arg1;
      wheel_speeds[1] = arg2;
      Serial.print("Motors speeds set are: ");
      Serial.print(wheel_speeds[0]);
      Serial.print(" ");
      Serial.print(wheel_speeds[1]);
      break;
    case 'z':
      Serial.print(argv1);
      Serial.print(' ');
      Serial.print(argv2);
      break;
  }
}

void resetCommand(){
  cmd = NULL;
  memset(argv1, 0, sizeof(argv1));
  memset(argv2, 0, sizeof(argv2));
  arg1 = 0;
  arg2 = 0;
  arg = 0;
  index = 0;
}


void readEncoders(){
  left_enc_value.getValue(readEncoder(LEFT));
  right_enc_value.getValue(readEncoder(RIGHT));
}
