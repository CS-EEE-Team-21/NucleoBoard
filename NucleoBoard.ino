
#include <Wire.h>

const int ESP_TO_NUCLEO_PORT = 9;
const int PH_PORT = 10;
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

    // temperature from the sensor
    case 'a':
      processSensorTemperature(receivedData);
      break;

    // pH from the sensor
    case 'b':
      processSensorpH(receivedData);
      break;

    // rpm from the sensor
    case 'c':
      processSensorStirringRPM(receivedData);
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

void processSensorTemperature(float pH){
  Serial.print("pH Data: ");
  Serial.println(pH);
}

void processSensorpH(float pH){
  Serial.print("pH Data: ");
  Serial.println(pH);
}

void processSensorStirringRPM(float pH){
  Serial.print("pH Data: ");
  Serial.println(pH);
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

float getTemperature(){
  ;
}

float getpH(){
  Wire.requestFrom(PH_PORT, 3);
  delay(50);
}

float getRPM(){
  ;
}

//////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  Wire.begin(ESP_TO_NUCLEO_PORT);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  pH = getpH();
  // do something about getting the readings from the sensors every so often
  // also do something about how the sensors will be controlled from this file
  delay(100);
}

