#include <Arduino.h>
#include "pH.h"

const int ACID_PUMP = 13;
const int ALKALI_PUMP = 12;

void controlPH(float pH){
    if (pH >= 5.5){
        digitalWrite(ACID_PUMP, HIGH);
        digitalWrite(ALKALI_PUMP, LOW);
    } else if (pH <= 4.8){
        digitalWrite(ACID_PUMP, LOW);
        digitalWrite(ALKALI_PUMP, HIGH);
    } 
}

char* yes(void){
  return "when you see it !!";
}