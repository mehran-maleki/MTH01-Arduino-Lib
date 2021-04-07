/*
  Made on Apr 04, 2021
  By MehranMaleki @ Electropeak
  https://electropeak.com/learn/
*/

//  Sensor top view
//  CS     -  On/Off   1|°     --------------   [][][][]
//  SCK    -  CLK      2|°    [              ]  [][][][]
//  SDAT   -  MOSI     3|°    [              ]  [][][][]
//  Reset  -  Reset    4|°    [              ]  [][][][]
//  VSS    -  GND      5|°     --------------   [][][][]
//  VDD    -  +5V      6|°                       °    °
//                        -----------------------------

//Arduino connections
// CS    ->  7
// SCK   ->  13
// SDAT  ->  11
// Reset ->  NC
// VSS   ->  GND
// VDD   ->  5V


#include <Arduino.h>
#include "MTH01.h"

#define mth01_pin 7   // define CS_pin

MTH01 mth01;
void setup()
{
  Serial.begin(9600);
  Serial.println("MTH-01 High Sensitivity Humidity & Temperature Sensor Module");
  mth01.begin(mth01_pin);   // Start the Sensor
}

void loop()
{
  Serial.print(" T = ");
  Serial.print(mth01.getTemperature());
  Serial.write("\xC2\xB0");   // The Degree symbol
  Serial.print("C");
  Serial.print("\t H = ");
  Serial.print(mth01.getHumidity());
  Serial.println("%");
  delay(5000);
}
