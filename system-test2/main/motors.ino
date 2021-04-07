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

/*macros*/
#define MAX_PWM 204 //(rated_volt=12V / max_volt=15V)*(max_analog_val=255) = 12/15*255 = 204
#define DEBUG 0

/*constants*/
const int XY_MIN = 0;
const int XY_MAX = 1023;
const int XY_CEN = 512;
const int INCR = 5;

/*globals*/
int x_speed = 0;
int y_speed = 0; 
int x_direction = 1;
int y_direction = 1;

int last_x_dir = 1;
int last_y_dir = 1;

void motors_init()
{
  /*motor initialization*/
  pinMode(motor13_enA, OUTPUT);
  pinMode(motor13_in1, OUTPUT);
  pinMode(motor13_in2, OUTPUT);
  pinMode(motor24_enA, OUTPUT);
  pinMode(motor24_in1, OUTPUT);
  pinMode(motor24_in2, OUTPUT);
}

void writeSpeeds(int x_val, int y_val, bool debug)
{
  //determines the displacement of the joystick, filter out values <= 100
  double x_displacement = abs(x_val-XY_CEN) <= 100 ? 0 : x_val-XY_CEN; //positive if go right; negative if go left
  double y_displacement = abs(y_val-XY_CEN) <= 100 ? 0 : y_val-XY_CEN; //positive if foward; negative if backward
  
  //maps absolute-valued displacement to pwm
  int x_speed_next = map(abs(x_displacement), XY_MIN, (XY_MAX-XY_CEN), 0, MAX_PWM);
  int y_speed_next = map(abs(y_displacement), XY_MIN, (XY_MAX-XY_CEN), 0, MAX_PWM);
  
  //determines directions of motors
  x_direction = (x_displacement > 0) ? 1 : 0; //1: EAST(COUNTERCLOCKWISE), 0: WEST(CLOCKWISE)
  y_direction = (y_displacement > 0) ? 1 : 0; //1: NORTH(COUNTERCLOCKWISE), 0: SOUTH(CLOCKWISE)

  //if this direction is different from last and while x_speed is still positive,
  //decrements speed to 0
  while ((x_direction != last_x_dir) && x_speed >= 1) {
    x_speed -= 10;
    if (x_speed <= 0) { x_speed = 0; }
    delay(DELAY);
    analogWrite(motor13_enA, x_speed);
  } 
  if (x_speed != x_speed_next) {
    x_speed += (x_speed_next - x_speed) > 0 ? INCR : -1*INCR;
    analogWrite(motor13_enA, x_speed);
  }

  //if this direction is different from last and while y_speed is still positive,
  //decrements speed to 0
  while ((y_direction != last_y_dir) && y_speed >= 1) {
    y_speed -= 10;
    if (y_speed <= 0) { y_speed = 0; }
    delay(DELAY);
    analogWrite(motor24_enA, y_speed);
  } 
  if (y_speed != y_speed_next) {
    y_speed += (y_speed_next - y_speed) > 0 ? INCR : -1*INCR;
    analogWrite(motor24_enA, y_speed);
  }

  //write x direction
  if (x_direction) { //if EAST
    digitalWrite(motor13_in1, HIGH);
    digitalWrite(motor13_in2, LOW);
  } else {
    digitalWrite(motor13_in1, LOW);
    digitalWrite(motor13_in2, HIGH);
  }

  //write y direction
  if (y_direction) { //if NORTH
    digitalWrite(motor24_in1, HIGH);
    digitalWrite(motor24_in2, LOW);
  } else {
    digitalWrite(motor24_in1, LOW);
    digitalWrite(motor24_in2, HIGH);
  }
  last_x_dir = x_direction;
  last_y_dir = y_direction;
}
