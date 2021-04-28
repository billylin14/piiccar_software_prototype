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
}

// Compute the speed and write to the motors using the output from the PID
void computeSpeed() 
{
  #if MOTOR_TEST
    //reset i to 0
    if (i == 6) { i = 0; }
    Serial.println(output[i]);
    int speedX = abs(output[i]);
    int speedY = speedX;
    int dirX = signbit(output[i++]);
    int dirY = dirX;
  #else
    int speedX = abs(OutputX); //abs(-255~255)
    int speedY = abs(OutputY);
    int dirX = signbit(OutputX); //1 if >=0, 0 if <0
    int dirY = signbit(OutputY);
   #endif
  /* motorX */
  //TODO: refer to system-test1 to write to the motors with analogWrite and digitalWrite
  //Also, think about using while loop to increment or if statement to slowly increase the speed.
  //but maybe that's not necessary.

  analogWrite(motor13_enA, speedX);
  digitalWrite(motor13_enA, dirX);
  digitalWrite(motor13_enA, 1-dirX);
  
  analogWrite(motor24_enA, speedY);
  digitalWrite(motor24_enA, dirY);
  digitalWrite(motor24_enA, 1-dirY);
}
