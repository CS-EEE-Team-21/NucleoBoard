#include <Arduino.h>
#include "heating.h"

float R1 = 9979;
float R2, temperature;

int acount = 0;
float adummyValues[] = {28.5, 29.0, 30.2, 29.8, 30.5, 29.3, 29.7, 30.4, 30.1, 29.9, 30.3, 28.9, 29.8, 30.2, 30.5, 29.6, 30.1, 29.7, 30.0, 29.4, 30.2, 29.8, 30.3, 29.5, 29.9};

float getVoltageFromThermistor(){
  float voltage = analogRead(thermistorPin);
  return voltage;
}

float convertVoltageToTemperature(float voltage){
  R2 = (R1 * (((float)voltage - 1.0) / 1023.0)) / (1 - (((float)voltage - 1.0) / 1023.0));
  temperature = (1/((1/298.15)+(log(R2/10000)/4220)));
  temperature = temperature - 273.15;
  return temperature;
}

float getTemperature(void){
  // voltage = getVoltageFromThermistor();
  // return convertVoltageToTemperature(voltage);
  int *countPtr = &acount;
  *countPtr = ((*countPtr) + 1) % 25;
  return adummyValues[acount];
}

