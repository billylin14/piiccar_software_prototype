#define VRx A1 //analog pin A1 for x coordinate
#define VRy A0 //analog pin A0 for y coordinate
#define VRsw 2 //digital pin D2 for z input (high/low) 

//#define bt_rx 0
//#define bt_tx 1
//
//#include <SoftwareSerial.h>
//SoftwareSerial BT(bt_rx, bt_tx);

void setup() {
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(VRsw, INPUT_PULLUP); //1 as unpressed, 0 as pressed
  Serial.begin(9600);
  
//  BT.begin(9600); //setting up baud rate
}

void loop() {
  /* reading joystick values */
  int x_val = analogRead(VRx);
  int y_val = analogRead(VRy);
  int z_val = digitalRead(VRsw);
//  digitalWrite(VRsw, HIGH);
  Serial.println(x_val);
  Serial.println(y_val);
  Serial.println(z_val);
  Serial.println();
  delay(500);
//  /* sending values to uno */
//  Bt.write(); //versus BT.print()
//  delay(50); //arbitrary delay, need to adjust later
  
}
