#include <Arduino.h>
#include "heating.h"

float R1 = 9979;
float R2, temperature;

float getVoltageFromThermistor(void){
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
  float voltage = getVoltageFromThermistor();
  return convertVoltageToTemperature(voltage);
}

