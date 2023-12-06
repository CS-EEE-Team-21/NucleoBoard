#include <Arduino.h>
#include "heating.h"

float targetTemperature = 30;

void controlTemperature(float temperature){
  if (temperature < (targetTemperature-1.5)) {
    Serial.println("heater on");
    digitalWrite(heaterGatePin, HIGH);
  } else {
    Serial.println("heater off");
    digitalWrite(heaterGatePin, LOW);
  }
}

void changeTargetTemperature(float temperature){
  float *temperature_ptr = &targetTemperature;
  *temperature_ptr = temperature;
}

void displayTemperature(void){
  Serial.print("Target temperature: ");
  Serial.println(targetTemperature);
}