#define motor1_enA  9  //PWM    
#define motor1_in1  8  //forward enable
#define motor1_in2  7  //backward enable

int motorDir = 1;
bool decrement_flag = false;
int motorSpeed = 0;

void setup() {
  //motor initialization
  pinMode(motor1_enA, OUTPUT);
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  digitalWrite(motor1_in1, motorDir);
  digitalWrite(motor1_in2, !motorDir);
  digitalWrite(13, motorDir);
  //button initialization
  pinMode(2, INPUT); //button
  attachInterrupt(digitalPinToInterrupt(2), button_ISR, CHANGE); //give an ISR to button
  //LED
  pinMode(13, OUTPUT); //LED for showing button press
  //debugging serial port
  Serial.begin(9600);
}

/* method 1 for changing direction: Ramp down to 0, turn, and ramp back up.*/
void button_ISR() {
  //debouncing
  static unsigned long last_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time-last_time > 200) {
    motorDir = !motorDir;
    decrement_flag = true;
  }
  last_time = interrupt_time;
}

void loop() {
  int pot_val = analogRead(A0); //read from potentiometer 0~1023
  int motorSpeed_next = map(pot_val, 0, 1023, 0, 255);
  double diff = motorSpeed_next - motorSpeed;
  if (decrement_flag && motorSpeed >= 1) {
    Serial.println("decrement!");
    motorSpeed -= 10;
    if (motorSpeed <= 0){
      decrement_flag = false;
      
      digitalWrite(motor1_in1, motorDir);
      digitalWrite(motor1_in2, !motorDir);
      digitalWrite(13, motorDir);
    }
    analogWrite(motor1_enA, motorSpeed);
  } else if (motorSpeed != motorSpeed_next){
    motorSpeed += diff > 0 ? 1 : -1;
    analogWrite(motor1_enA, motorSpeed);
  }
//  Serial.print("new data ");
//  Serial.println(motorSpeed_next);
//  Serial.print("current data ");
//  Serial.println(motorSpeed);
  delay(1);
}

/*method 2 for changing direction: brake for n seconds and change direction without ramping down speed*/
/*
void button_ISR() {
  //debouncing
  static unsigned long last_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time-last_time > 200) {
    motorDir = !motorDir;
    //brake for 0.5s then reverse
    digitalWrite(motor1_in1, LOW);
    digitalWrite(motor1_in2, LOW);
    delay(1000); //delay for 1 sec
    Serial.println("brake!");
    digitalWrite(motor1_in1, motorDir);
    digitalWrite(motor1_in2, !motorDir);
    digitalWrite(13, motorDir);
  }
  last_time = interrupt_time;
}

void loop() {
  int pot_val = analogRead(A0); //read from potentiometer 0~1023
  int motorSpeed_next = map(pot_val, 0, 1023, 0, 255);
  double diff = motorSpeed_next - motorSpeed;
  if (motorSpeed != motorSpeed_next){
    motorSpeed += diff > 0 ? 1 : -1;
    analogWrite(motor1_enA, motorSpeed);
  }
//  Serial.print("new data ");
//  Serial.println(motorSpeed_next);
//  Serial.print("current data ");
//  Serial.println(motorSpeed);
  delay(1);
}
*/
