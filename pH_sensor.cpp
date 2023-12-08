#include <Arduino.h>
#include "pH.h"

float pHValue;

// int count = 0;
// float dummyValues[] = {3.0, 3.4, 3.1, 3.6, 3.4, 3.5, 4.0, 3.7, 3.6, 3.6, 3.5, 3.5, 3.3, 3.3, 3.3, 3.2, 3.5, 3.2, 3.2, 3.2, 2.9, 3.1, 3.2, 3.5, 3.2};

float getVoltageFromPHSensor(){
  float voltage = analogRead(PH_SENSOR)*5.0/1024;
  return voltage;
}

float convertVoltageToPH(float voltage){
  pHValue = (1.4047*voltage) + 2.8795;
  return pHValue;
}

float getPH(void){
  float voltage = getVoltageFromPHSensor();
  float pHValue = convertVoltageToPH(voltage);

  if (pHValue < 6) {
    pHValue = pHValue - 0.55;
  }
  else if (pHValue > 7.5) {
    pHValue = pHValue + 0.55;
  }

  return pHValue;
  // int *countPtr = &count;
  // *countPtr = ((*countPtr) + 1) % 25;
  // return dummyValues[count];
}