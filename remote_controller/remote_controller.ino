#define VRx A6 //analog pin A1 for x coordinate
#define VRy A7 //analog pin A0 for y coordinate
#define VRsw 2 //digital pin D2 for z input (high/low) 
#define DELAY 100

#include <SoftwareSerial.h>
SoftwareSerial hc05(3, 4); // RX | TX
// Connect the HC-05 TX to Arduino pin 3 RX. 
// Connect the HC-05 RX to Arduino pin 4 TX through a voltage divider.


void setup() {
  /*joystick initialization*/
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(VRsw, INPUT_PULLUP); //1 as unpressed, 0 as pressed

  /*bluetooth initialization*/
  Serial.begin(9600);
  hc05.begin(9600); 
}

void loop() {
  /* reading joystick values*/
  int raw_x = analogRead(VRx);
  int raw_y = analogRead(VRy);
//  int raw_z = digitalRead(VRsw);
  
  /*precompute speeds here*/
  uint8_t x = map(raw_x, 0, 1023, 0, 255);
  uint8_t y = map(raw_y, 0, 1023, 0, 255);
  hc05.write(x);
  hc05.write(y);
  Serial.print("raw_x = ");
  Serial.println(raw_x);
  Serial.print("raw_x = ");
  Serial.println(raw_x);
  Serial.print("x = ");
  Serial.println(x);
  Serial.print("y = ");
  Serial.println(y);
  delay(DELAY);
}
