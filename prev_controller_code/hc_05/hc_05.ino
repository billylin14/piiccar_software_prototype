
#include <SoftwareSerial.h>
SoftwareSerial hc05(3, 4); // (RX|TX)
char c = ' ';
#define VRx A6 //analog pin A1 for x coordinate
#define VRy A7 //analog pin A0 for y coordinate
#define VRsw 2 //digital pin D2 for z input (high/low) 

void setup() {
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(VRsw, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Arduino with HC-05 is ready");
  hc05.begin(9600);
  Serial.println("BTserial.started at 9600");
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.println("X-axis tilt:");
//  Serial.println("Y-axis tile:");
  int x = analogRead(VRx);
  int y = analogRead(VRy);
  delay(800);
  hc05.write(x);
  hc05.write(y);
  if (hc05.available()){
    int received = hc05.read();
    Serial.write(received);
  }
//  if (Serial.available()){
//     c = Serial.read();
//     hc05.write(c);
//     Serial.write(c);
//  }
}
