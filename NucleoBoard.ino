
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
  uint16_t receivedData = word(intByte1, intByte2);

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
  Serial.print(temperature);
  Serial.println("°C");
}

void processReceivedpH(float pH){
  pH /= 100;
  Serial.print("pH: ");
  Serial.println(pH);
}

void processReceivedStirringRPM(int rpm){
  Serial.print("Motor RPM: ");
  Serial.println(rpm);
}

///////////////////////// NUCLEOBOARD TO ESP32 COMMUNICATION //////////////////////////////////

float temperature = 31.42;
float pH = 6.9696987;
float rpm = 2023.465236;

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
  // do something about getting the readings from the sensors every so often
  // also do something about how the sensors will be controlled from this file
  delay(100);
}

