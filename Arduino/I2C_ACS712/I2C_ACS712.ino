#include <ACS712.h>
#include <Wire.h>

#define I2C_ADDRESS 8
#define ACS712_SENSOR_1_PIN 0
#define ACS712_SENSOR_2_PIN 1
#define MAINS_FREQUENCY 60 // US

double sensor1Amps = 0;
double sensor2Amps = 0;

ACS712 sensor1(ACS712_20A, ACS712_SENSOR_1_PIN);
ACS712 sensor2(ACS712_20A, ACS712_SENSOR_2_PIN);

void setup() {
  // mid point of ADC
  sensor1.setZeroPoint(512);
  sensor2.setZeroPoint(512);
  
  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(sendData);
}

void loop() {
  // update current 
  sensor1Amps = sensor1.getCurrentAC(MAINS_FREQUENCY);
  sensor2Amps = sensor2.getCurrentAC(MAINS_FREQUENCY);
}

void sendData(){
  // send the current data as 16bits representing milliamps, first 2 bytes for first sensor and last 2 bytes for second sensor
  unsigned short mAmps1 = sensor1Amps * 1000;
  unsigned short mAmps2 = sensor2Amps * 1000;
  byte bytes[4] = { (byte)((mAmps1 >> 8) & 0xff), (byte)(mAmps1 & 0xff), 
                    (byte)((mAmps2 >> 8) & 0xff), (byte)(mAmps2 & 0xff) };
  Wire.write(bytes, 4);
}

