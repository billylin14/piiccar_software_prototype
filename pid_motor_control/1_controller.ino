#include <SoftwareSerial.h>
SoftwareSerial hc06(2, 3); // RX | TX (of the hc06)
//#define DELAY 100
int x = 0; //joystick X
int y = 0; //joystick Y
double setpointX;
double setpointY;
const int MAXBIAS = 20;


// Initialize bluetooth connection
void bluetooth_init(){
  hc06.begin(9600); //setting up baud rate
  
}

// Read the input from the hc06 bluetooth connection
void readController() {
  while (hc06.available())
  {
      x = (int)hc06.read();
      y = (int)hc06.read();
  }
//  Serial.print("x=");
//  Serial.println(x);
//  Serial.print("y=");
//  Serial.println(y);

  
  
}

int currentDesiredAngleX = 0;
int currentDesiredAngleY = 0;

//use the values read from the controller, determine the desired angle for the pid control, also, increment the output desired angle
void getDesireAngle() {
  
  //x, y's range is 0~255, map to -20~20 degree
  int desiredAngleX = map(x, 0, 255, -1 * MAXBIAS + 1, MAXBIAS);
  int desiredAngleY = map(y, 0, 255, -1 * MAXBIAS + 1, MAXBIAS);

  if (currentDesiredAngleX < desiredAngleX) {
    currentDesiredAngleX ++;
  }
  else if (currentDesiredAngleX > desiredAngleX) {
    currentDesiredAngleX --;
  }
  if (currentDesiredAngleY < desiredAngleY) {
    currentDesiredAngleY ++;
  }
  else if (currentDesiredAngleY > desiredAngleY) {
    currentDesiredAngleY --;
  }
//  Serial.print("current desired angle x: ");
//  Serial.println(currentDesiredAngleX);
//  Serial.print("desired angle x: ");
//  Serial.println(desiredAngleX);
}
  
  

  
