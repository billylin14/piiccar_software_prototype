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
                         
void motor_init() {
  /*motor initialization*/
  pinMode(motor13_enA, OUTPUT);
  pinMode(motor13_in1, OUTPUT);
  pinMode(motor13_in2, OUTPUT);
  pinMode(motor24_enA, OUTPUT);
  pinMode(motor24_in1, OUTPUT);
  pinMode(motor24_in2, OUTPUT);
}
