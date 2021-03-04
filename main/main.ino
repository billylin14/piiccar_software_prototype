#include "motors.h"

/*globals*/
int motorSpeeds[4];
int motorDir[4];


void setup() {
  /*motor initialization*/
  motors_init();

  /*bluetooth initialization*/
  //BT.begin(9600); //setting up baud rate
}

void loop() {
  /*
  //receive commands from bluetooth
  //if (BT.available()>0)
  //{
  //  //updates input values
  //}
  */
  //temp data, remove later when bluetooth module implemented
  double x_val = 0; //joystick x position
  double y_val = 0; //joystick y position
  //map x_val, y_val to pwm output
  getSpeeds();
  //send commands to pins
  
}
