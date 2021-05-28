/* 
 *  Read the Adafruit LSM9DS1 sensor and calculate the angle from the sensor data.
 *  Calculation of angle is partially adopted from James Bruton's BB8 robot 
 *  (https://github.com/XRobots/3D_BB8_Public/blob/master/BB813/BB813.ino)
 *  
 *  ECE 498 ENGINE Capstone-Spring 2021
 *  Authors: Billy Lin, Ariel Chang
 *  Last update: May-27-2021
 */
 
#include <Wire.h> //i2c library
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

// macros
#define dt 0.002

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
    Serial.println("unable to initialize the LSM9DS1.");
    while (1);
  }
  
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G); //range of accelerometer
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS); //sensitivity of magnetometer
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS); //range of gyroscope
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
  
  angleX = (0.95)*(angleX + gyro_x * dt) + (0.05)*pitchAccel;
  angleY = (0.95)*(angleY + gyro_y * dt) + (0.05)*rollAccel;
}
