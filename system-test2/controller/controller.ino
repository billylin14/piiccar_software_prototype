#define VRx A6 //analog pin A1 for x coordinate
#define VRy A7 //analog pin A0 for y coordinate
#define VRsw 2 //digital pin D2 for z input (high/low) 

///*motors globals*/
//uint8_t x_speed = 0;
//uint8_t y_speed = 0; 
//uint8_t x_direction = 1;
//uint8_t y_direction = 1;

//uint8_t last_x_dir = 1;
//uint8_t last_y_dir = 1;

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
  int x_val = analogRead(VRx);
  int y_val = analogRead(VRy);
  int z_val = digitalRead(VRsw);

  String dataPacket = packageVals(x_val, y_val, z_val);
  for (int i = 0; i < dataPacket.length(); i++) {
    hc05.write(dataPacket.charAt(i));
  }
//  x_speed = getSpeeds(x_val, x_speed, last_x_dir, false);
//  y_speed = getSpeeds(y_val, y_speed, last_y_dir, false);
//  hc05.write(x_val);
//  hc05.write(y_val);
//  hc05.write(z_val);
//  Serial.println(x_val);
//  Serial.println(y_val);
//  Serial.println(z_val);
//  Serial.println();
  delay(1000);
//  /* sending values to uno */
//  Bt.write(); //versus BT.print()
//  delay(50); //arbitrary delay, need to adjust later
  
}

String packageVals(int x_val, int y_val, int z_val) {
  String x_4 = String(int(x_val / 1000));   // 0
  String x_3 = String(int((x_val % 1000) / 100));   // 5
  String x_2 = String(int((x_val % 100) / 10));   // 2
  String x_1 = String(x_val % 10);   // 4
  String y_4 = String(int(y_val / 1000));
  String y_3 = String(int((y_val % 1000) / 100));
  String y_2 = String(int((y_val % 100) / 10));
  String y_1 = String(y_val % 10);
  String z = String(z_val);
  return String(x_4+x_3+x_2+x_1+y_4+y_3+y_2+y_1+z);
}
