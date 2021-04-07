#define VRx A6 //analog pin A1 for x coordinate
#define VRy A7 //analog pin A0 for y coordinate
#define VRsw 2 //digital pin D2 for z input (high/low) 

//#define bt_rx 0
//#define bt_tx 1
//
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
  /* reading joystick values */
  uint8_t x_val = analogRead(VRx);
  uint8_t y_val = analogRead(VRy);
  uint8_t z_val = digitalRead(VRsw);
  hc05.write(x_val);
  hc05.write(y_val);
  hc05.write(z_val);
//  digitalWrite(VRsw, HIGH);
  Serial.println(x_val);
  Serial.println(y_val);
  Serial.println(z_val);
  Serial.println();
  delay(25);
//  /* sending values to uno */
//  Bt.write(); //versus BT.print()
//  delay(50); //arbitrary delay, need to adjust later
  
}
