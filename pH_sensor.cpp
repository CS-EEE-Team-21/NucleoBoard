#include <Arduino.h>
#include "pH.h"

float pHValue;
float voltage;

int count = 0;
float dummyValues[] = {3.0, 3.4, 3.1, 3.6, 3.4, 3.5, 4.0, 3.7, 3.6, 3.6, 3.5, 3.5, 3.3, 3.3, 3.3, 3.2, 3.5, 3.2, 3.2, 3.2, 2.9, 3.1, 3.2, 3.5, 3.2};

float getVoltage(){
  voltage = analogRead(PH_SENSOR)*5.0/1024;
  return voltage;
}

float convertVoltageToPH(float voltage){
  pHValue = (1.4047*voltage) + 2.8795;
  return pHValue;
}

float getPH(void){
  // voltage = getVoltage();
  // return convertVoltageToPH(voltage);
  int *countPtr = &count;
  *countPtr = ((*countPtr) + 1) % 25;
  return dummyValues[count];
}