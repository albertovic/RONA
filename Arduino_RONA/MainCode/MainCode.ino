#include "PIDController.h"
#include "motor.h"
#include "motors_controller.h"
#include "motor_pins.h"
#include "encoder.h"
#include "commands.h"

#define BAUD_RATE 9600

const unsigned long sampleTime = 20;  // Sample time in miliseconds

unsigned long lastComputeTime = 0;

int kp = 0;
int ki = 0;
int kd = 0;
int input = 0;

// Creation of a controller object (PID)
MotorController controller = MotorController(kp, ki, kd);

// Creation of the motor objects
Motor left_motor = Motor(LEFT_MOTOR_PWM, LEFT_MOTOR_FORWARD, LEFT_MOTOR_BACKWARD);
Motor right_motor = Motor(RIGHT_MOTOR_PWM, RIGHT_MOTOR_FORWARD, RIGHT_MOTOR_BACKWARD);

EncoderValues left_enc_value = EncoderValues();
EncoderValues right_enc_value = EncoderValues();

void setup() {
  controller.addMotor(left_motor);
  controller.addMotor(right_motor);
  controller.addEncoderValue(left_enc_value);
  controller.addEncoderValue(right_enc_value);

  Serial.begin(BAUD_RATE);

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

void loop() {
  unsigned long currentTime = millis();
  double wheel_speeds[2];

  // TODO SERIAL COMMUNICATION

  // Verify if the sample time has passed
  if (currentTime - lastComputeTime >= sampleTime) {

    //Update the 4 motor speeds
    controller.updateMotorSpeeds(wheel_speeds);
    
    // Update reference time
    lastComputeTime = millis();
  }
}

void readEncoders(){
  left_enc_value.getValue(readEncoder(LEFT));
  right_enc_value.getValue(readEncoder(RIGHT));
}
