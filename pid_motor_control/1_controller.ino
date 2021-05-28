/* 
 *  HC-06 Bluetooth receiver code.
 *  
 *  ECE 498 ENGINE Capstone-Spring 2021
 *  Authors: Billy Lin, Ariel Chang, Junyi Wu
 *  Last update: May-27-2021
 */
 
#include <SoftwareSerial.h>
SoftwareSerial hc06(2, 3); // RX | TX (of the hc06)
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
      x = hc06.read();
      y = hc06.read();
  }
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
}
