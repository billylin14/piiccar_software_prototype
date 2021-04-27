#include <SoftwareSerial.h>
SoftwareSerial hc06(2, 3); // RX | TX (of the hc06)
//#define DELAY 100
int x = 0; //joystick X
int y = 0; //joystick Y

// Initialize bluetooth connection
void bluetooth_init(){
  hc06.begin(9600); //setting up baud rate
  
}

// Read the input from the hc06 bluetooth connection
void readController() {
  while (hc06.available())
  {
      x = hc06.read();
      y = hc06.read();
  }
  Serial.print("x=");
  Serial.println(x);
  Serial.print("y=");
  Serial.println(y);
}

//TODO: use the values read from the controller, determine the desired angle for the pid control, also, increment the output desired angle
void getDesireAngle() {
  
}
