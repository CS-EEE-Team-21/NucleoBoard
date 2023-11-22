#include "I2C.h"
#include <Wire.h>

void setup(){
    Serial.begin(9600);
    Wire.begin(); // Join the bus as master
}

void loop() {
  Wire.beginTransmission(8); // Transmit to device with address 8
  Wire.write("Hello, Slave!"); // Sends text to the slave device
  Wire.endTransmission(); // Stop transmitting

  delay(500);
}