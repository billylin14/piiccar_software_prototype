/* Pin definitions */
#define motor1_en  2      
#define motor1_pwm 3
#define motor2_en  7   
#define motor2_pwm 6
#define motor3_en  8    
#define motor3_pwm 9
#define motor4_en  12    
#define motor4_pwm 11

#define bt_rx 0
#define bt_tx 1

#include <SoftwareSerial.h>
SoftwareSerial BT(bt_rx, bt_tx);

//joystick positions
double x_val = 0;
double y_val = 0;

typedef struct
{
  double motorSpeed;
  bool motorDirection; //1: forward 0: backward
}motorSpeeds, *motor1_data, *motor2_data, *motor3_data, *motor4_data;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1_en, OUTPUT);
  pinMode(motor1_pwm, OUTPUT);
  pinMode(motor2_en, OUTPUT);
  pinMode(motor2_pwm, OUTPUT);
  pinMode(motor3_en, OUTPUT);
  pinMode(motor3_pwm, OUTPUT);
  pinMode(motor4_en, OUTPUT);
  pinMode(motor4_pwm, OUTPUT);
  
  BT.begin(9600); //setting up baud rate
}

void getSpeed()
{
  
}

void updateInput()
{
  
}

void loop() {
  //receive commands from bluetooth
  if (BT.available()>0)
  {
    //updates input values
    Serial.read();
    updateInput();
  }
  //map x_val, y_val to pwm output
  getSpeed();
  //send commands to pins
  
}
