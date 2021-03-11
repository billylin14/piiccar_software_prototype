/* temp joystick definitions */
#define VRx A0 //analog pin A0 for x coordinate
#define VRy A1 //analog pin A1 for y coordinate
#define VRsw 2 //digital pin D2 for z input (high/low) 

const int DELAY = 25;

void setup() {
  /*motor initialization*/
  motors_init();

  /*joystick initialization*/
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(VRsw, INPUT_PULLUP); //1 as unpressed, 0 as pressed
  /*bluetooth initialization*/
  //BT.begin(9600); //setting up baud rate
  Serial.begin(9600);
}

void loop() {
  /*
  //receive commands from bluetooth
  //if (BT.available()>0)
  //{
  //  //updates input values
  //}
  */
  /*receive commands*/
  int x_val = analogRead(VRx); //joystick x position
  int y_val = analogRead(VRy); //joystick y position
  int z_val = digitalRead(VRsw);
//  Serial.println(x_val);
//  Serial.println(1023-y_val);
  //map x_val, y_val to pwm output
  writeSpeeds(x_val, 1023-y_val, true); //invert y_axis to make forward >512, backward <512
  delay(DELAY);
}
