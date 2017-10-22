/*
* I2C ACS712
* Copyright (c) 2017 bbtinkerer
*
* Attiny85 program that returns the current RMS value of two ACS712 sensors 
* via I2C. Returns 4 bytes (2 bytes per sensor MSB formatted) representing the 
* current values in milliamps. The first 2 bytes for the first sensor and last 
* two bytes for the second sensor.
*
* Default addresses selected by Pin 6 (PB1)
*  GND -> 0x08
*  VCC -> 0x09 (don't forget the 10K resistor)
* 
* Libraries Used (besides Arduino):
* ACS712-arduino by Ruslan Koptev, https://github.com/rkoptev/ACS712-arduino
* USIWire by puuu, https://github.com/puuu/USIWire
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Arduino.h>
#include <ACS712.h>
#include <USIWire.h>

//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio

#define I2C_ADDRESS_START 8
#define I2C_ADDRESS_PIN 1
#define ACS712_SENSOR_1_ADC 2
#define ACS712_SENSOR_2_ADC 3
#define MAINS_FREQUENCY 60 // US

double sensor1Amps = 0;
double sensor2Amps = 0;

// change the first argument to match your sensor
ACS712 sensor1(ACS712_20A, ACS712_SENSOR_1_ADC);
ACS712 sensor2(ACS712_20A, ACS712_SENSOR_2_ADC);

void sendData();

// the setup function runs once when you press reset or power the board
void setup() {
   // determine which address to use
   // if PB1 is high, use I2C_ADDRESS_START + 1, else if PB1 is low use I2C_ADDRESS_START
   pinMode(I2C_ADDRESS_PIN, INPUT);
   int address = I2C_ADDRESS_START + digitalRead(I2C_ADDRESS_PIN);
   
   Wire.begin(address);
   Wire.onRequest(sendData);
   // initialize digital pin LED_BUILTIN as an output.
   pinMode(0, OUTPUT);
}

// the loop function runs over and over again forever
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