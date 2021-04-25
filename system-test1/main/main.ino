#include <SoftwareSerial.h>
SoftwareSerial hc06(2, 3); // RX | TX
#define DELAY 100

void setup() {
  /*bluetooth initialization*/
  hc06.begin(9600); //setting up baud rate
  Serial.begin(9600);

  motors_init();
}

void loop() {
  uint8_t x_speed = 0;
  uint8_t y_speed = 0;
  uint8_t x_dir = 0;
  uint8_t y_dir = 0;
  int x = 0;
  int y = 0;
  /*receive commands from bluetooth*/
  while (hc06.available())
  {
    // updates input values
//    x_speed = hc06.read();
//    x_dir = hc06.read();
//    y_speed = hc06.read();
//    y_dir = hc06.read();
      x = hc06.read();
      y = hc06.read();
  }
  Serial.print("x=");
  Serial.println(x);
  Serial.print("y=");
  Serial.println(y);
  //  Serial.println(x_speed);
//  Serial.println(x_dir);
//  Serial.println(y_speed);
//  Serial.println(y_dir);
//  Serial.println();
  
  //map x_val, y_val to pwm output
//  writeSpeeds(x_val, 1023-y_val, true); //invert y_axis to make forward >512, backward <512
  
  delay(DELAY);
}
