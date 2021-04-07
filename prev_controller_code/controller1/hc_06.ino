//#include <SoftwareSerial.h>
//SoftwareSerial BTserial(2,3); // RX | TX
//
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//  Serial.println("Arduino with HC-06 is ready");
//
//  BTserial.begin(9600);
//  Serial.println("BTserial started at 9600");
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  if (BTserial.available()){
//     Serial.write(BTserial.read());
//  }
//  if (Serial.available()){
//    BTserial.write(Serial.read());
//  }
//}
