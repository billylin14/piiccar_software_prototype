// joystick :  (0,0) ^ (1023,0)
//                   |
//               < - . - >
//                   |
//         (0, 1023) v (1023, 1023)
#include <SoftwareSerial.h>
SoftwareSerial hc05(0, 1); // (RX|TX)
char c = ' ';
#define VRx A6 //analog pin A1 for x coordinate
#define VRy A7 //analog pin A0 for y coordinate
#define VRsw 2 //digital pin D2 for z input (high/low) 

void setup() {
  // put your setup code here, to run once:
//  pinMode(SW1, OUTPUT);
//  digitalWrite(SW1, HIGH);
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
  Serial.print("X-axis tilt:");
  Serial.println(analogRead(VRx));
  Serial.print("Y-axis tile:");
  Serial.println(analogRead(VRy));
  delay(800);
  if (hc05.available()){
    Serial.write(hc05.read());
  }
  if (Serial.available()){
     c = Serial.read();
     hc05.write(c);
     Serial.write(c);
  }
}
