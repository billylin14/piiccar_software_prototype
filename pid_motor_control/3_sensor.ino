/* includes */
#include <Wire.h> //i2c library
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

// macros
#define dt 0.001

// define a struct datatype for the sensors that stores information about x, y, z
typedef struct Sensor //object type
{
  float x;
  float y;
  float z;
} Sensor; //object name

/* global variables */
float angleX = 0; //sensor output angle in X direction
float angleY = 0; //sensor output angle in Y direction
Sensor acceleration; //sensor data x,y,z for the acceleration
Sensor gyro; //sensor data x,y,z for the gyroscope
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(); //instance of the lsm9ds1 sensor 


// Setup the sensor configurations
void setupSensor()
{
  //check if the wiring of the sensor is correct
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G); //maximum: 10
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G); //doesn't work somehow
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G); //maximum: 120
  
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

// Read sensor values and store in the sensor sturcts for easy access
void readSensor() 
{
  /* ask it to read in the data */
  lsm.read();  
  
  /* Get a new sensor event */ 
  sensors_event_t a, m, g, temp;
  lsm.getEvent(&a, &m, &g, &temp); 

  /* Update struct data */
  acceleration.x = a.acceleration.x;
  acceleration.y = a.acceleration.y;
  acceleration.z = a.acceleration.z;

  gyro.x = g.gyro.x;
  gyro.y = g.gyro.y;
  gyro.z = g.gyro.z;
}

// Calculate angles in X and Y directions using the translational speed and angular speed
void calculateAngle() 
{
  float x = acceleration.x;
  float y = acceleration.y;
  float z = acceleration.z;
  double rollAccel = atan2(x, sqrt(y * y) + (z * z));
  double pitchAccel = atan2(y, sqrt(x * x) + (z * z));
  pitchAccel *= 180.0 / PI;
  rollAccel *= 180.0 / PI;
  pitchAccel = pitchAccel +0.2;    // zero out pitch and roll based on IMU mounting
  rollAccel = rollAccel +0.1;
  float gyro_x = gyro.x;
  float gyro_y = gyro.y - 0.09;
//  Serial.println(gyro_x);
//  Serial.println(gyro_y);
//  Serial.println();

//  Serial.print("pitch Accel");
//  Serial.println(pitchAccel);
//  Serial.print("roll Accel");
//  Serial.println(rollAccel);
  
  angleX = (0.95)*(angleX + gyro_x * dt) + (0.05)*pitchAccel;
  angleY = (0.95)*(angleY + gyro_y * dt) + (0.05)*rollAccel;
  
  Serial.println(angleX);
  Serial.println(angleY);
}
