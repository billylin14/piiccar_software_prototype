#include <PID_v2.h> //pid control library
#define PID_SAMPLE_TIME 100 //ms
                         
int Kp; //do our own experiment to set the parameters!
int Ki;
int Kd;

double SetpointY, InputY, OutputY;    // PID variables
double SetpointX, InputX, OutputX;    // PID variables

PID PIDY(&InputY, &OutputY, &SetpointY, Kp, Ki, Kd, DIRECT);    // Y axis PID
PID PIDX(&InputX, &OutputX, &SetpointX, Kp, Ki, Kd, DIRECT);    // X Axis PID

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
