/* Pin definitions 
 * Notice:
 * motor 1 and 3, 2 and 4 share the same signals
 */  
#define motor13_enA  3  //           {}{1}{}
#define motor13_in1  2  //           __||__
#define motor13_in2  4  //      {}  [      ]  {}   
#define motor24_enA  5  //     {4}--[      ]--{2}
#define motor24_in1  6  //      {}  [__  __]  {}
#define motor24_in2  7  //             ||
                        //           {}{3}{}

/*macros*/
#define MAX_PWM 204 //(rated_volt=12V / max_volt=15V)*(max_analog_val=255) = 12/15*255 = 204


/*constants*/
const int XY_MIN = 0;
const int XY_MAX = 1023;
const int XY_CEN = 512;

/*globals*/
int motorSpeed_X;
int motorSpeed_Y;
int motorDir_X;
int motorDir_Y;

void motors_init()
{
  /*motor initialization*/
  pinMode(motor13_enA, OUTPUT);
  pinMode(motor13_in1, OUTPUT);
  pinMode(motor13_in2, OUTPUT);
  pinMode(motor24_enA, OUTPUT);
  pinMode(motor24_in1, OUTPUT);
  pinMode(motor24_in2, OUTPUT);
  motorSpeed_X = 0;
  motorSpeed_Y = 0;
  motorDir_X = 0;
  motorDir_Y = 0;
}

void writeSpeeds(int x_val, int y_val)
{
  //determines the displacement of the joystick, filter out values <= 100
  double x_displacement = abs(x_val-XY_CEN) <= 100 ? 0 : x_val-XY_CEN;
  double y_displacement = abs(y_val-XY_CEN) <= 100 ? 0 : y_val-XY_CEN;
  
  //maps absolute-valued displacement to pwm
  int motorSpeed_X_next = map(abs(x_displacement), XY_MIN, (XY_MAX-XY_CEN), 0, MAX_PWM);
  int motorSpeed_Y_next = map(abs(y_displacement), XY_MIN, (XY_MAX-XY_CEN), 0, MAX_PWM);
  float diff_X = motorSpeed_X_next - motorSpeed_X;
  float diff_Y = motorSpeed_Y_next - motorSpeed_Y;
  
  //ramp function
  if (motorSpeed_X != motorSpeed_X_next) {
    motorSpeed_X += diff_X > 0 ? 1 : -1;
    analogWrite(motor13_enA, motorSpeed_X);
  }
  if (motorSpeed_Y != motorSpeed_Y_next) {
    motorSpeed_Y += diff_Y > 0 ? 1 : -1;
    analogWrite(motor24_enA, motorSpeed_X);
  }
  
  //maps displacement to direction
  if (x_displacement < 0) { //change direction
    //brake for n milliseconds
    brake();
    delay(1000); //CAUTION: need at least 500 ms
    motorDir_X = !motorDir_X;
  } 
  if (y_displacement >= 0) {
    //brake for n milliseconds
    brake();
    delay(1000);
    motorDir_Y = !motorDir_Y;
  } 
  digitalWrite(motor13_in1, motorDir_X);
  digitalWrite(motor13_in2, !motorDir_X);
  digitalWrite(motor24_in1, motorDir_Y);
  digitalWrite(motor24_in2, !motorDir_Y);
}
void brake()
{
  digitalWrite(motor13_in1, LOW);
  digitalWrite(motor13_in2, LOW);
  digitalWrite(motor24_in1, LOW);
  digitalWrite(motor24_in2, LOW);
}
