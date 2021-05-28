/* 
 *  Motor driver subprogram of the ball-balancing robot (prototype 2)
 *  
 *  ECE 498 ENGINE Capstone-Spring 2021
 *  Authors: Billy Lin, Ariel Chang, Junyi Wu
 *  Last update: May-27-2021
 */

/* Pin definitions 
 * Notice:
 * motor 1 and 3, 2 and 4 share the same signals
 */  
#define motor24_enA  9  //           {}{1}{}
#define motor24_in1  8  //           __||__
#define motor24_in2  7  //      {}  [      ]   {}   
#define motor13_enA  11  //    {4}--[      ]--{2}
#define motor13_in1  12  //     {}  [__  __]   {}
#define motor13_in2  13  //            ||
                         //          {}{3}{}
#define C 43

#define MOTOR_TEST 1
//simulate possible output values to feed to the motors
#if MOTOR_TEST
  int i = 0;
  int output[] = { 10, -10, 5, 20, -20, 50 };
#endif
// Configure the pin connections of the motors
void motor_init() 
{
  /*motor initialization*/
  pinMode(motor13_enA, OUTPUT);
  pinMode(motor13_in1, OUTPUT);
  pinMode(motor13_in2, OUTPUT);
  pinMode(motor24_enA, OUTPUT);
  pinMode(motor24_in1, OUTPUT);
  pinMode(motor24_in2, OUTPUT);
  analogWrite(motor24_enA, 0);
  analogWrite(motor13_enA, 0);
  digitalWrite(motor24_in1, 0);
  digitalWrite(motor24_in2, 0);
  digitalWrite(motor13_in1, 0);
  digitalWrite(motor13_in2, 0);
}

// Compute the speed and write to the motors using the output from the PID
void computeSpeed() 
{
  int speedX = map(abs(OutputX), 0, 255, C, 204);
  int speedY = map(abs(OutputY), 0, 255, C, 204);
  int dirX = 0;
  int dirY = 0;
  if (OutputX >= 0) {
    dirX = 1;
  } else {
    dirX = 0;
  }
  if (OutputY >= 0) {
    dirY = 0;
  } else {
    dirY = 1;
  }
  /* motorX */
  analogWrite(motor24_enA, speedX);
  digitalWrite(motor24_in1, dirX);
  digitalWrite(motor24_in2, 1-dirX);
  
  analogWrite(motor13_enA, speedY);
  digitalWrite(motor13_in1, dirY);
  digitalWrite(motor13_in2, 1-dirY);
}
