/*macros*/
#define MAX_PWM 204 //(rated_volt=12V / max_volt=15V)*(max_analog_val=255) = 12/15*255 = 204
#define DEBUG 0

/*constants*/
const int XY_MIN = 0;
const int XY_MAX = 1023;
const int XY_CEN = 512;
const int INCR = 5;

/*global*/

void getSpeed(int raw_val, struct motor_t * motor) {
  int displacement = abs(raw_val-XY_CEN) <= 100 ? 0 : raw_val-XY_CEN; //positive if go right; negative if go left
  int nextSpeed = map(abs(displacement), XY_MIN, (XY_MAX-XY_CEN), 0, MAX_PWM);
  uint8_t nextDir;
  if (displacement > 0) { nextDir = 1; }
  else if (displacement < 0) { nextDir = 0; }
  else { nextDir = motor->dir; } 
  /*
  if (this dir != last dir) {
    flag = 1
  }
  if (flag && speed != 0) {
    motor speed - 20
    if (motor speed <= 0){ motor speed = 0; }
  if (speed == 0 } {
    motor dir = !motor dir
    flag = 0
  } else if (motor speed != next motor speed) {
    motor speed + 10;
  }
  */
  if (motor->dir != nextDir) {
    Serial.println("FLAG ON");
    motor->dir_flag = 1;
  } 
  if (motor->dir_flag && motor->spd != 0) {
//    Serial.println("DECELERATING");
    if (((int)motor->spd)-10 <= 0) { 
      motor->spd = 0; 
      motor->dir_flag = 0;
      motor->dir = nextDir;
      Serial.println("CHANGE DIRRRRRR");
    } else {
      motor->spd -= 10;
      Serial.println("PENALIZEEEEEEEEEEEEEEEEE");
    }
  }else if (motor->spd != nextSpeed) {
    if ((nextSpeed - motor->spd) < 0 && ((int)motor->spd)-(-1*INCR) <= 0) { motor->spd = 0; }
    else {
      motor->spd += (nextSpeed - motor->spd) > 0 ? INCR : -1*INCR;
    }
  }
  
  
  /*ver1
  //determines the displacement of the joystick, filter out values <= 100
  double displacement = abs(raw_val-XY_CEN) <= 100 ? 0 : raw_val-XY_CEN; //positive if go right; negative if go left
  
  //maps absolute-valued displacement to pwm
  int next_speed = map(abs(displacement), XY_MIN, (XY_MAX-XY_CEN), 0, MAX_PWM);
  
  //determines directions of motors
  motor.dir = (displacement > 0) ? 1 : 0; 
  
  //if this direction is different from last and while x_speed is still positive,
  //decrements speed to 0
  while ((motor.dir != motor.last_dir) && motor.currentSpeed >= 1) {
    motor.currentSpeed -= 10;
    if (motor.currentSpeed <= 0) { motor.currentSpeed = 0; }
    delay(DELAY);
  } 
  if (motor.currentSpeed != next_speed) {
    motor.currentSpeed += (next_speed - motor.currentSpeed) > 0 ? INCR : -1*INCR;
  }
  
  motor.lastDir = motor.dir;
  */
}
