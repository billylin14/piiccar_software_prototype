#include <SoftwareSerial.h>
SoftwareSerial hc06(2, 3); // RX | TX
//#define DELAY 100
int x = 0;
int y = 0;
/*bluetooth initialization*/
void bluetooth_init(){
  hc06.begin(9600); //setting up baud rate
  
}

void readController() {
  while (hc06.available())
  {
      x = hc06.read();
      y = hc06.read();
  }
  Serial.print("x=");
  Serial.println(x);
  Serial.print("y=");
  Serial.println(y);
}
