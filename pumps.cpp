#include <Arduino.h>
#include "pH.h"

float targetPH = 5;

void controlPH(float pH){
    if (pH >= targetPH + 0.5){
        Serial.println("acid pumps on alkali pumps off");
        digitalWrite(ACID_PUMP, HIGH);
        digitalWrite(ALKALI_PUMP, LOW);
    } else if (pH <= targetPH - 0.5){
        Serial.println("acid pumps off alkali pumps on");
        digitalWrite(ACID_PUMP, LOW);
        digitalWrite(ALKALI_PUMP, HIGH);
    } 
}

void changeTargetPH(float pH){
    float *pH_ptr = &targetPH;
    *pH_ptr = pH;
}

void displayPH(void){
  Serial.print("Target pH: ");
  Serial.println(targetPH);
}