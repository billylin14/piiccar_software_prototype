#include <Wire.h> //i2c library
#include <PID_v1.h> //pid control library

/* Pin definitions 
 * Notice:
 * motor 1 and 3, 2 and 4 share the same signals
 */  
#define motor13_enA  9  //           {}{1}{}
#define motor13_in1  8  //           __||__
#define motor13_in2  7  //      {}  [      ]   {}   
#define motor24_enA  11  //    {4}--[      ]--{2}
#define motor24_in1  12  //     {}  [__  __]   {}
#define motor24_in2  13  //            ||
                         //          {}{3}{}
#define PID_SAMPLE_TIME 100 //ms
                         
int Kp; //do our own experiment to set the parameters!
int Ki;
int Kd;

double SetpointY, InputY, OutputY;    // PID variables
double SetpointX, InputX, OutputX;    // PID variables

PID PIDY(&InputY, &OutputY, &SetpointY, Kp, Ki, Kd, DIRECT);    // Y axis PID
PID PIDX(&InputX, &OutputX, &SetpointX, Kp, Ki, Kd, DIRECT);    // X Axis PID

void sensor_init() {
  
}

void motor_init() {
  /*motor initialization*/
  pinMode(motor13_enA, OUTPUT);
  pinMode(motor13_in1, OUTPUT);
  pinMode(motor13_in2, OUTPUT);
  pinMode(motor24_enA, OUTPUT);
  pinMode(motor24_in1, OUTPUT);
  pinMode(motor24_in2, OUTPUT);
}

void PID_init() {
  PIDY.SetMode(AUTOMATIC); //turn on (Automatic) / off (Manual)
  PIDY.SetOutputLimits(-255, 255);    // limits for PID loops (0~255 range for motor PWM, +-255 for two directions)
  PIDX.SetMode(AUTOMATIC);
  PIDX.SetOutputLimits(-255, 255);
  PIDY.SetSampleTime(PID_SAMPLE_TIME);
  PIDX.SetSampleTime(PID_SAMPLE_TIME);

  //set desired angle (set SetpointX, Y)
  SetpointY = 0;      // Desired value for PID loops
  SetpointX = 0; 
}

void setup() {
  // put your setup code here, to run once:
  sensor_init();
  motor_init();
  PID_init();
}

void loop() {
  readController();   //get joystick values
  setDesiredAngle();  //update setpointX/setpointY
  readSensor();       //get sensor values
  calculateAngle();   //update inputX/inputY
  PIDY.Compute();     //update outputX/outputY
  PIDX.Compute();     
  computeSpeed();     //use outputX,Y to map to speed & direction
}
