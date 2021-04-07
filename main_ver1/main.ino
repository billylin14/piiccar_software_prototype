#include <SoftwareSerial.h>
SoftwareSerial hc06(2, 3); // RX | TX

const int DELAY = 25;

void setup() {
  /*bluetooth initialization*/
  hc06.begin(9600); //setting up baud rate
  Serial.begin(9600);

  motors_init();
}

void loop() {
  uint8_t x_val = 0;
  uint8_t y_val = 0;
  uint8_t z_val = 0;
  
  /*receive commands from bluetooth*/
  while (hc06.available())
  {
    // updates input values
    x_val = (uint8_t)hc06.read();
    y_val = (uint8_t)hc06.read();
    z_val = (uint8_t)hc06.read();
  }
  
  Serial.println((int)x_val);
  Serial.println((int)y_val);
  Serial.println(z_val);
  
  //map x_val, y_val to pwm output
  writeSpeeds(x_val, 1023-y_val, true); //invert y_axis to make forward >512, backward <512
  Serial.println("Finish executing");
  Serial.println();
  delay(DELAY);
}
