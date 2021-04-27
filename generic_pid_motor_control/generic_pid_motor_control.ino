extern float angleX;
extern float angleY;

extern int x = 0;
extern int y = 0;

void setup() {
  // put your setup code here, to run once:
  setupSensor();
//  motor_init();
//  PID_init();
  bluetooth_init();

  /* debug console */
  Serial.begin(9600);

//  while (!Serial) {
//    delay(1); // will pause Zero, Leonardo, etc until serial console opens
//  }

  
}

void loop() 
{
  readController();   //get joystick values
  readSensor();       //read sensor values - DONE
  calculateAngle();   //calculate angles from acc and gyro - DONE
  /*put these functions in pid function*/
//  setDesiredAngle();  //update setpointX/setpointY
//  InputX = angleX;
//  InputY = angleY;
//  PIDY.Compute();     //update outputX/outputY
//  PIDX.Compute();     
//  /*************/
//  computeSpeed();     //use outputX,Y to map to speed & direction
  delay(10);
}
