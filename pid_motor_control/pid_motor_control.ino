extern float angleX; //sensor output angle in X direction
extern float angleY; //sensor output angle in Y direction

//extern int x = 0; //joystick X
//extern int y = 0; //joystick Y

// Main setup of the robot
void setup() {
  setupSensor();
  motor_init();
  PID_init();
  bluetooth_init();

  /* debug console */
  Serial.begin(9600);
}

// Main function flow of the robot
void loop() 
{

//  readController();   //get joystick values
  getDesireAngle();   //map joystick values to desired angle (for SetpointX/Y)
  readSensor();       //read sensor values - DONE
  calculateAngle();   //calculate angles from acc and gyro - DONE
  PID_update();       //use the calculated results to update PID variables
  computeSpeed();     //use outputX,Y to map to speed & direction
  delay(1);


}
