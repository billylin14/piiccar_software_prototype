#include <SoftwareSerial.h>
SoftwareSerial hc06(2, 3); // RX | TX

const int DELAY = 500;


void setup() {
  /*bluetooth initialization*/
  hc06.begin(9600); //setting up baud rate
  Serial.begin(9600);

  motors_init();
}

void loop() {
  String message = "";
  /*receive commands from bluetooth*/
  while (hc06.available())
  {
    // updates input values
    message += (char)hc06.read();
  }
//  Serial.println(message);
  int x_val = message.substring(0, 4).toInt();
  int y_val = message.substring(4, 8).toInt();
  int z_val = message.substring(8).toInt();
  Serial.println(x_val);
  Serial.println(y_val);
  
  //map x_val, y_val to pwm output
  writeSpeeds(x_val, 1023-y_val, true); //invert y_axis to make forward >512, backward <512
  
  delay(DELAY);
}
