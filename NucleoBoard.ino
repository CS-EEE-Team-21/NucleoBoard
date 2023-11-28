
#include <Wire.h>

const int ESP_TO_NUCLEO_PORT = 9;
// const int phSensor = ?
// const int temperatureSensor = ?
// const int stirringSensor = ?

///////////////////////////// NUCLEOBOARD FROM ESP32 COMMUNICATION ////////////////////////////////

void receiveEvent(int howMany) {
  // To send the sensor values, it is transmitted in chunks of bytes
  char subsystem = Wire.read();
  byte intByte1 = Wire.read();
  byte intByte2 = Wire.read();
  float receivedData = (intByte1 << 8) | intByte2;

  switch (subsystem){
    case 't':
      processReceivedTemperature(receivedData);
      break;
    case 'p':
      processReceivedpH(receivedData);
      break;
    case 's':
      processReceivedStirringRPM(receivedData);
      break;
    default:
      Serial.print("Unexpected subsystem '");
      Serial.print(subsystem);
      Serial.print("' received. ");
  }
}

void processReceivedTemperature(float temperature){
  temperature /= 100;
  Serial.print("Temperature: ");
  Serial.println(temperature);
}

void processReceivedpH(float pH){
  pH /= 100;
  Serial.print("pH: ");
  Serial.println(pH);
}

void processReceivedStirringRPM(float rpm){
  Serial.print("Motor RPM: ");
  Serial.println(rpm);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void requestEvent() {
  Wire.write("hello ");
}

void setup() {
  Serial.begin(9600);
  Wire.begin(ESP_TO_NUCLEO_PORT);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(100);
}

