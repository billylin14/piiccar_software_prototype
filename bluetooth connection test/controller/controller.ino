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

char c = ' ';
 
void setup() 
{
    // start th serial communication with the host computer
    Serial.begin(9600);
    Serial.println("Arduino with HC-05 is ready");
 
    // start communication with the HC-05 using 38400
    hc05.begin(9600);  
    Serial.println("BTserial started at 38400");
}
 
void loop()
{
   // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (hc05.available())  {  
    c = hc05.read();
    Serial.print((char)c);
  }

//  // Keep reading from Arduino Serial Monitor and send to HC-05
//  if (Serial.available()) {
//    c =  Serial.read();
//
//    // mirror the commands back to the serial monitor
//    // makes it easy to follow the commands
////    Serial.print(c);   
//    hc05.write(c);  
//  }
 
}
