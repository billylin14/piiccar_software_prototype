#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

// i2c
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

//#define LSM9DS1_SCK A5
//#define LSM9DS1_MISO 12
//#define LSM9DS1_MOSI A4
//#define LSM9DS1_XGCS 6
//#define LSM9DS1_MCS 5
// You can also use software SPI
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS, LSM9DS1_MCS);
// Or hardware SPI! In this case, only CS pins are passed in
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_XGCS, LSM9DS1_MCS);
#define dt 0.01
float angleX = 0;
float angleY = 0;

void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G); //maximum: 10
//  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G); //doesn't work somehow
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
//  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G); //maximum: 120
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}


void setup() 
{
  Serial.begin(9600);

  while (!Serial) {
    delay(1); // will pause Zero, Leonardo, etc until serial console opens
  }
  
  Serial.println("LSM9DS1 data read demo");
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");

  // helper to just set the default scaling we want, see above!
  setupSensor();
}


void loop() 
{
  lsm.read();  /* ask it to read in the data */ 

  /* Get a new sensor event */ 
  sensors_event_t a, m, g, temp;

  lsm.getEvent(&a, &m, &g, &temp); 

  Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.println(" m/s^2");
  Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.println(" m/s^2 ");
  Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");

//  Serial.print("Mag X: "); Serial.print(m.magnetic.x);   Serial.print(" uT");
//  Serial.print("\tY: "); Serial.print(m.magnetic.y);     Serial.print(" uT");
//  Serial.print("\tZ: "); Serial.print(m.magnetic.z);     Serial.println(" uT");

//  Serial.print("Gyro X: "); Serial.print(g.gyro.x);   Serial.print(" rad/s");
//  Serial.print("\tY: "); Serial.print(g.gyro.y);      Serial.print(" rad/s");
  //Serial.print("\tZ: "); Serial.print(g.gyro.z);      Serial.println(" rad/s");

  /* calculating angle: method by James Bruton */
//  double x=a.acceleration.x;                          // extra variables to make the next section look cleaner
//  double y=a.acceleration.y;
//  double z=a.acceleration.z;
//  
//  double pitchAccel = atan2(x, sqrt(y * y) + (z * z));
//  double rollAccel = atan2(y, sqrt(x * x) + (z * z));
//  pitchAccel *= 180.0 / PI;
//  rollAccel *= 180.0 / PI;
//  
//  pitchAccel = pitchAccel +0.08;    // zero out pitch and roll based on IMU mounting
//  rollAccel = rollAccel -0.3;
//
//  angleX = (0.98)*(angleX + g.gyro.x * dt) + (0.02)*pitchAccel;
//  angleY = (0.98)*(angleY + g.gyro.y * dt) + (0.02)*rollAccel;
//
//  Serial.print("Angle_X\t"); Serial.println(angleX);
//  Serial.print("Angle_Y\t"); Serial.println(angleY);
//  Serial.println();


  Serial.println();
  delay(500);
}
