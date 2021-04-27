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

typedef struct Motor //object type
{
  uint8_t Speed;
  uint8_t Dir;
} Motor; //object name

Motor motor1, motor2, motor3, motor4;

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

void computeSpeed() 
{
  int speedX = abs(OutputX); //abs(-255~255)
  int speedY = abs(OutputY);
  int dirX = OutputX >= 0 ? 1: -1;
  int dirY = OutputY >= 0 ? 1: -1;
  /* motorX */
  //TODO: refer to system-test1 to write to the motors with analogWrite and digitalWrite
  //Also, think about using while loop to increment or if statement to slowly increase the speed.
  //but maybe that's not necessary.
}
