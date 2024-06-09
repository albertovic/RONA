int ENA = 11;
int IN1 = 9;
int IN2 = 8;

int motor_speed = 220;

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, motor_speed);

}
