#include <Wire.h>
#include "pH.h"

const int ESP_TO_NUCLEO_PORT = 9;
// const int temperatureSensor = ?
// const int stirringSensor = ?

float temperature;
float pH;
float rpm;

///////////////////////////// NUCLEOBOARD FROM ESP32 COMMUNICATION ////////////////////////////////

void receiveEvent(int howMany) {
  // To send the sensor values, it is transmitted in chunks of bytes
  Serial.println("Message received");
  char subsystem = Wire.read();
  byte intByte1 = Wire.read();
  byte intByte2 = Wire.read();
  uint16_t receivedData = word(intByte1, intByte2);

  switch (subsystem){
    // temperature from the esp32
    case 't':
      processESPTemperature(receivedData);
      break;

    // pH from the esp32
    case 'p':
      processESPpH(receivedData);
      break;

    // rpm from the esp32
    case 's':
      processESPStirringRPM(receivedData);
      break;

    default:
      Serial.print("Unexpected subsystem '");
      Serial.print(subsystem);
      Serial.print("' received. ");
  }
}

void processESPTemperature(float temperature){
  temperature /= 100;
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
}

void processESPpH(float pH){
  pH /= 100;
  Serial.print("pH: ");
  Serial.println(pH);
}

void processESPStirringRPM(int rpm){
  Serial.print("Motor RPM: ");
  Serial.println(rpm);
}

///////////////////////// NUCLEOBOARD TO ESP32 COMMUNICATION //////////////////////////////////

void requestEvent() {
  uint16_t temperatureData = (int)round(temperature * 100);
  uint16_t pHData = (int)round(pH * 100);
  uint16_t rpmData = (int)round(rpm);
  Wire.write(highByte(temperatureData));
  Wire.write(lowByte(temperatureData));
  Wire.write(highByte(pHData));
  Wire.write(lowByte(pHData));
  Wire.write(highByte(rpmData));
  Wire.write(lowByte(rpmData));
}

//////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  Wire.begin(ESP_TO_NUCLEO_PORT);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  // pH = getPH();
  // Serial.print("pH: ");
  // Serial.println(pH);
  // controlPH(pH);
  delay(100);
}

