#include <PID_v2.h> //pid control library
#define PID_SAMPLE_TIME 100 //ms

extern float angleX; //sensor output angle in X direction
extern float angleY; //sensor output angle in Y direction

//do our own experiment to set the parameters!
int Kp = 0;  //proportion parameter in PID
int Ki = 0;  //integral parameter in PID
int Kd = 0;  //derivative parameter in PID

double SetpointY, InputY, OutputY;    // PID variables (Setpoint = desired, Input = sensor, Output = motor)
double SetpointX, InputX, OutputX;    // PID variables

PID PIDY(&InputY, &OutputY, &SetpointY, Kp, Ki, Kd, DIRECT);    // Y axis PID object 
PID PIDX(&InputX, &OutputX, &SetpointX, Kp, Ki, Kd, DIRECT);    // X Axis PID object

// Setup the PID objects
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

// Update the PID variables and compute the output
void PID_update() {
  InputX = angleX;
  InputY = angleY;
  SetpointX = 0; //change this later
  SetpointY = 0; //change this later
  PIDX.Compute();
  PIDY.Compute();
}
