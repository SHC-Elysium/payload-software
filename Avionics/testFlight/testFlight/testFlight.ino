#include <Wire.h>
#include <Arduino_LSM6DS3.h>
#include <Adafruit_LPS2X.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>


// flying with altimu
// barretts radio
// teensy 4.1
// pololu stepper motor
// possibly gps

void sampleSensors();

// LSM6
  float acelX, acelY, acelZ;
// LPS
  Adafruit_LPS25 lps;
  #define CS 10
  #define SCK 13
  #define MISO 12
  #define MOSI 11
  float lpsTemp, press;
//LIS
  Adafruit_LIS3MDL lis3mdl;
  float magX, magY, magZ;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
  //LSM6 Setup 
    // !!!!!!!!!!!!
    // look into spi
    // !!!!!!!!!!!!
    if (!IMU.begin()) { Serial.println("Failed to initialize IMU!");  }
  //LPS
    if (!lps.begin_SPI(CS, SCK, MISO, MOSI)) {Serial.println("Failed to find LPS25 chip");  }
    lps.setDataRate(LPS25_RATE_25_HZ);
  //LIS
    if (!lis3mdl.begin_SPI(CS, CLK, MISO, MOSI)) {  Serial.println("Failed to find LIS3MDL chip");}
    lis3mdl.setPerformanceMode(LIS3MDL_HIGHMODE);
    lis3mdl.setDataRate(LIS3MDL_DATARATE_300_HZ);
    lis3mdl.setRange(LIS3MDL_RANGE_8_GAUSS); 
    lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);





}

void loop() {
  // put your main code here, to run repeatedly:
  sampleSensors();

}

void sampleSensors(){

  //LSM6
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(x, y, z);  
    }
  //LPS
    sensors_event_t temp;
    sensors_event_t pressure;
    lps.getEvent(&pressure, &temp);
    lpsTemp = temp.temperature;
    press = pressure.pressure;

  //LIS
    lis3mdl.read();      // get X Y and Z data at once
    sensors_event_t event; 
    lis3mdl.getEvent(&event);
    magX = event.magnetic.x;
    magY = event.magnetic.Y;
    magZ = event.magnetic.Z;




  #ifdef debug
    Serial.print("Accelerometer Data: ");
    Serial.print(acelX);
    Serial.print(", ");
    Serial.print(acelY);
    Serial.print(", ");
    Serial.println(acelZ);
    Serial.print("BMP Data: ");
    Serial.print(lpsTemp);
    Serial.print(", ");
    Serial.println(press);
    Serial.print("Magnetometer Data: ");
    Serial.print(magX);
    Serial.print(", ");
    Serial.print(magY);
    Serial.print(", ");
    Serial.println(magZ);
  #endif 
}