extern float angleX; //sensor output angle in X direction
extern float angleY; //sensor output angle in Y direction

// Main setup of the robot
void setup() {
  setupSensor();
  motor_init();
  PID_init();
  //bluetooth_init(); //bluetooth module not used in 2nd prototype

  /* debug console */
  Serial.begin(9600);
}

// Main function flow of the robot
void loop() 
{

//  readController();   //get joystick values, not used in 2nd prototype
  getDesireAngle();   //map joystick values to desired angle (for SetpointX/Y)
  readSensor();       //read sensor values - DONE
  calculateAngle();   //calculate angles from acc and gyro - DONE
  PID_update();       //use the calculated results to update PID variables
  computeSpeed();     //use outputX,Y to map to speed & direction

}
