#define input_x  //analog pin for x coordinate
#define input_y //analog pin for y coordinate
#define input_en //digital pin for enabling the joystick 

#define bt_rx 0
#define bt_tx 1

#include <SoftwareSerial.h>
SoftwareSerial BT(bt_rx, bt_tx);

void setup() {
  // put your setup code here, to run once:
  pinMode(input_en, INPUT);
  digitalWrite(input_en, HIGH); //enable the joystick

  BT.begin(9600); //setting up baud rate
}

void loop() {
  // put your main code here, to run repeatedly:
  /* reading joystick values */
  double x_val = analogRead(input_x);
  double y_val = analogRead(input_y);
  /* sending values to uno */
  Bt.write(); //versus BT.print()
  delay(50); //arbitrary delay, need to adjust later
  
}
