/* Pin definitions */
#define motor1_en  2      
#define motor1_pwm 3
#define motor2_en  7   
#define motor2_pwm 6
#define motor3_en  8    
#define motor3_pwm 9
#define motor4_en  12    
#define motor4_pwm 11

/*macros*/
#define MAX_PWM 204 //(rated_volt=12V / max_volt=15V)*(max_analog_val=255) = 12/15*255 = 204


/*constants*/
const int XY_MIN = 0;
const int XY_MAX = 1023;
const int XY_CEN = 512;

/*globals*/
extern int motorSpeeds[4];
extern int motorDir[4]; //1 as HIGH, 0 as LOW

void motors_init()
{
  /*motor initialization*/
  pinMode(motor1_en, OUTPUT);
  pinMode(motor1_pwm, OUTPUT);
  pinMode(motor2_en, OUTPUT);
  pinMode(motor2_pwm, OUTPUT);
  pinMode(motor3_en, OUTPUT);
  pinMode(motor3_pwm, OUTPUT);
  pinMode(motor4_en, OUTPUT);
  pinMode(motor4_pwm, OUTPUT);
  motorSpeeds = {0, 0, 0, 0};
}

void getSpeeds(int x_val, int y_val)
{
  //determines the displacement of the joystick, filter out values <= 100
  double x_displacement = abs(x_val-XY_CEN) <= 100 ? 0 : x_val-XY_CEN;
  double y_displacement = abs(y_val-XY_CEN) <= 100 ? 0 : y_val-XY_CEN;
  
  //maps absolute-valued displacement to pwm
  motorSpeed[0] = map(abs(x_displacement), XY_MIN, (XY_MAX-XY_CEN), 0, MAX_PWM);
  motorSpeed[1] = map(abs(y_displacement), XY_MIN, (XY_MAX-XY_CEN), 0, MAX_PWM);
  motorSpeed[2] = map(abs(x_displacement), XY_MIN, (XY_MAX-XY_CEN), 0, MAX_PWM);
  motorSpeed[3] = map(abs(y_displacement), XY_MIN, (XY_MAX-XY_CEN), 0, MAX_PWM);

  //maps displacement to direction
  motorDir[0] = x_displacement > 0 ? HIGH : LOW; //clockwise (HIGH) as positive, counterclockwise (LOW) as negative <- TODO: confirm this
  motorDir[1] = y_displacement > 0 ? HIGH : LOW; 
  motorDir[2] = x_displacement > 0 ? HIGH : LOW; //clockwise (HIGH) as positive, counterclockwise (LOW) as negative
  motorDir[3] = y_displacement > 0 ? HIGH : LOW; //clockwise (HIGH) as positive, counterclockwise (LOW) as negative
  
  
}

void getMotor1Speed(double x_val, double y_val)
{
  
}
