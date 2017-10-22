#include <Wire.h>

void setup()
{
  Wire.begin();

  Serial.begin(115200);
  while (!Serial); 
  Serial.println("\nI2C Test for I2C_ACS712 on Addresses 8 and 9");
}

void loop()
{
  printValues(8);
  printValues(9);
  Serial.println("========================================");
  delay(1000);  
}

void printValues(int address){
  byte bytes[2];
  int index = 0;
  Wire.requestFrom(address, 4);
  if(Wire.available()){
    while(Wire.available())
    {
      bytes[index++] = Wire.read();
    }
    float amps1 = ((short)((bytes[0] << 8) & 0xFF00) | bytes[1] & 0xFF)/1000.0;
    float amps2 = ((short)((bytes[2] << 8) & 0xFF00) | bytes[3] & 0xFF)/1000.0;
    Serial.print("Address: ");
    Serial.print(address);
    Serial.print("   IRMS01: " ); Serial.print(amps1); Serial.print("    IRMS02: " ); Serial.println(amps2);
  }
}

