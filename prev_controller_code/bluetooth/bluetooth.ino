//#include <SoftwareSerial.h>
//SoftwareSerial BTserial(2, 3); // RX | TX
//// Connect the HC-05 TX to Arduino pin 7 RX. 
//// Connect the HC-05 RX to Arduino pin  8 TX through a voltage divider.
//// 
//
//char c = ' ';
//char c1 = ' ';
//int flag = 0;
//int x_val = 0;
//int y_val = 0;
//int z_val = 0;
//String x_4 = " ";
//String x_3 = " ";
//String x_2 = " ";
//String x_1 = " ";
//String y_4 = " ";
//String y_3 = " ";
//String y_2 = " ";
//String y_1 = " ";
//String z = " ";
//String total = " ";
//
//void setup() 
//{
//    Serial.begin(9600);
//    Serial.println("Arduino is ready");
//    Serial.println("Remember to select Both NL & CR in the serial monitor");
//    
//    // HC-05 default serial speed for AT mode is 38400
//    BTserial.begin(9600);  
//}
//
//void loop()
//{   
//    x_val = 524;
//    y_val = 523;
//    z_val = 1;
//    
//    String x_4 = String(int(x_val / 1000));   // 0
//    String x_3 = String(int((x_val % 1000) / 100));   // 5
//    String x_2 = String(int((x_val % 100) / 10));   // 2
//    String x_1 = String(x_val % 10);   // 4
//    String y_4 = String(int(y_val / 1000));
//    String y_3 = String(int((y_val % 1000) / 100));
//    String y_2 = String(int((y_val % 100) / 10));
//    String y_1 = String(y_val % 10);
//    String z = String(z_val);
//    String total = String(x_4+x_3+x_2+x_1+y_4+y_3+y_2+y_1+z);
//    
//    // Keep reading from HC-05 and send to Arduino Serial Monitor
//    /*if (BTserial.available())
//    {  
//        c = BTserial.read();
//        Serial.write(c);
//    }*/
//    
//    // Keep reading from Arduino Serial Monitor and send to HC-05
//    if (Serial.available())
//    {   
//        c1 = Serial.read();
//        //BTserial.write(c1);
//        
//        if (c1 == 'a'){
//          BTserial.write('e');
//          BTserial.write('n');
//          BTserial.write('d');
//          flag = 1;
//        } else if (c1 != ' '){
//          flag = 0;
//        } 
//        
//        if (flag == 0){
//          for (int i = 0; i < 9; i++){
//             c = total.charAt(i);
//             BTserial.write(c);
//          }
//        }
//        /*
//        for (int i = 0; i < 9; i++){
//             c = total.charAt(i);
//             BTserial.write(c);
//        }
//        delay(200);*/
//        //c1 = Serial.read();
//        //BTserial.write(c1);  
//    }
//}
