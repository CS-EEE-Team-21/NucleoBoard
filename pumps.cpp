#include <Arduino.h>
#include "pH.h"

float targetPH = 5;

void controlPH(float pH){
    if (pH >= targetPH + 0.1){
        Serial.println("acid pumps on alkali pumps off");
        digitalWrite(ACID_PUMP, HIGH);
        digitalWrite(ALKALI_PUMP, LOW);
        delay(80);
        digitalWrite(ACID_PUMP, LOW);
    } else if (pH <= targetPH - 0.1){
        Serial.println("acid pumps off alkali pumps on");
        digitalWrite(ACID_PUMP, LOW);
        digitalWrite(ALKALI_PUMP, HIGH);
        delay(80);
        digitalWrite(ALKALI_PUMP, LOW);
    } 
}

void changeTargetPH(float pH){
    float *pH_ptr = &targetPH;
    *pH_ptr = pH;
}

void displayTargetPH(void){
  Serial.print("Target pH: ");
  Serial.println(targetPH);
}