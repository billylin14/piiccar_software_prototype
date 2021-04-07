#include <SoftwareSerial.h>
SoftwareSerial hc06(2, 3); // RX | TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  Serial.println("Arduino with HC-06 is ready");

  // HC-06 default baud rate is 9600
  hc06.begin(9600);  
//  Serial.println("BTserial started at 9600");
}

void loop() {
  // Keep reading from HC-06 and send to Arduino Serial Monitor
  if (hc06.available()) {
    uint8_t c = hc06.read();
    Serial.println((uint8_t)c);
  }
//  // Keep reading from Arduino Serial Monitor and send to HC-06
//  if (Serial.available()) {
//    char c = Serial.read();
////    Serial.print(c); 
//    hc06.write(c);
//  }
}
