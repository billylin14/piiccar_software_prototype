/* 
 *  PID controller of the ball-balancing robot
 *  
 *  ECE 498 ENGINE Capstone-Spring 2021
 *  Authors: Billy Lin, Ariel Chang
 *  Last update: May-27-2021
 */
 
#include <PID_v2.h> //pid control library
#define PID_SAMPLE_TIME 2 //ms

extern float angleX; //sensor output angle in X direction
extern float angleY; //sensor output angle in Y direction

double Kp = 8.5;  //proportion parameter in PID //Kp is the current error 
double Ki = 0.5;  //integral parameter in PID //Ki should be either small or zero //Ki is the sum of the errors for each sample
double Kd = 0.1;  //derivative parameter in PID //Kd measures the change of error in each sample

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
  InputX = angleY;
  InputY = angleX;
  SetpointX = 0;//currentDesiredAngleX; 
  SetpointY = 0;//currentDesiredAngleY;
  PIDX.Compute();
  PIDY.Compute();
}
