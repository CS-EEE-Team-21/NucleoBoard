#include <Arduino.h>
#include "pH.h"

const int ACID_PUMP = 13;
const int ALKALI_PUMP = 12;
float targetPH = 5;

void controlPH(float pH){
    if (pH >= targetPH + 0.5){
        digitalWrite(ACID_PUMP, HIGH);
        digitalWrite(ALKALI_PUMP, LOW);
    } else if (pH <= targetPH - 0.5){
        digitalWrite(ACID_PUMP, LOW);
        digitalWrite(ALKALI_PUMP, HIGH);
    } 
}

void changePH(float pH){
    float *pH_ptr = &targetPH;
    *pH_ptr = pH;
}

char* yes(void){
  return "when you see it !!";
}