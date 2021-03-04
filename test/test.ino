#define motor1_enA  9  //PWM    
#define motor1_in1  8  //forward enable
#define motor1_in2  7  //backward enable

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1_enA, OUTPUT);
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  Serial.begin(9600);
  pinMode(2, INPUT); //button
  pinMode(13, OUTPUT); //LED for showing button press
}

int button = 0;
int motorSpeed = 0;
int count = 0; //count up to sampling freq

void loop() {
  // put your main code here, to run repeatedly
  int pot_val = analogRead(A0); //read from potentiometer 0~1023
  int pressed = digitalRead(2); 
  if (pressed) { button = !button; } //toggle button based on pressing the button
  digitalWrite(motor1_in1, button);
  digitalWrite(motor1_in2, !button); //TODO <- determine which is clockwise/counterclockwise
  digitalWrite(13, button); //show the button value on LED
  int motorSpeed_next = map(pot_val, 0, 1023, 0, 255);
  //ramp function
  double diff = motorSpeed_next - motorSpeed;
  while (motorSpeed != motorSpeed_next)
  {
    motorSpeed += diff > 0 ? 1: -1;
    analogWrite(motor1_enA, motorSpeed);
    Serial.print("new data ");
    Serial.println(motorSpeed_next);
    Serial.print("current data ");
    Serial.println(motorSpeed);
    delay(50);
  }
  delay(100); //sample every 100 ms
}
