#define VRx A6 //analog pin A1 for x coordinate
#define VRy A7 //analog pin A0 for y coordinate
#define VRsw 2 //digital pin D2 for z input (high/low) 
#define DELAY 10

//#define bt_rx 0
//#define bt_tx 1
//
#include <SoftwareSerial.h>
SoftwareSerial hc05(3, 4); // RX | TX
// Connect the HC-05 TX to Arduino pin 3 RX. 
// Connect the HC-05 RX to Arduino pin 4 TX through a voltage divider.

/*globals*/
typedef struct motor_t {
  uint8_t spd;
  uint8_t dir;
  uint8_t dir_flag;
};

motor_t x_motor;
motor_t y_motor;

void setup() {
  /*joystick initialization*/
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(VRsw, INPUT_PULLUP); //1 as unpressed, 0 as pressed

  /*bluetooth initialization*/
  Serial.begin(9600);
  hc05.begin(9600); 

  /*motor value init*/
  x_motor.spd = 0;
  x_motor.dir = 1;
  x_motor.dir_flag = 0;
  y_motor.spd = 0;
  y_motor.dir = 1;
  y_motor.dir_flag = 0;
}

void loop() {
  /* reading joystick values*/
  int raw_x = analogRead(VRx);
  int raw_y = analogRead(VRy);
  int raw_z = digitalRead(VRsw);
  
  /*precompute speeds here*/
  getSpeed(raw_x, &x_motor);
  getSpeed(raw_y, &y_motor);
  hc05.write(x_motor.spd);
  hc05.write(x_motor.dir);
  hc05.write(y_motor.spd);
  hc05.write(y_motor.dir);
  Serial.println(x_motor.spd);
  Serial.println(y_motor.spd);
//  if (x_motor.dir == 1){
//    Serial.println("GO EAST");
//  } else {
//    Serial.println("GO WEST");
//  }
//  if (y_motor.dir == 1){
//    Serial.println("GO NORTH");
//  } else {
//    Serial.println("GO SOUTH");
//  }
//  hc05.write(z_val);
//  digitalWrite(VRsw, HIGH);
//  Serial.println(x_val);
//  Serial.println(y_val);
//  Serial.println(z_val);
//  Serial.println();
  delay(DELAY);
//  /* sending values to uno */
//  Bt.write(); //versus BT.print()
//  delay(50); //arbitrary delay, need to adjust later
}
