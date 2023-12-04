/*
 # This sample code is used to test the pH meter V2.0.
 # Editor : Vincent
 # Ver    : 2.0
 # Product: analog pH meter
 # SKU    : SEN0161
*/

#include <Arduino.h>
#include "pH_sensor.h"

#define SensorPin A0
#define offset 2.8795

float pHValue;
float voltage;

// Stores the average of 40 samples of the voltage
float getVoltage(){
  voltage = analogRead(SensorPin)*5.0/1024;
  return voltage;
}

float convertVoltageToPH(float voltage){
  pHValue = (1.4047*voltage) + offset;
  return pHValue;
}

float getPH(void){
  voltage = getVoltage();
  return convertVoltageToPH(voltage);
}

char* yes(void){
  return "when you see it !!";
}