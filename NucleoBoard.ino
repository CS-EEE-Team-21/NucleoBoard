#include <Wire.h>
#include "pH.h"

const int ESP_TO_NUCLEO_PORT = 9;

float averageTemperature;
float averagePH;
float averageRPM;

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
  changeTargetPH(pH);
}

void processESPStirringRPM(int rpm){
  Serial.print("Motor RPM: ");
  Serial.println(rpm);
}

///////////////////////// NUCLEOBOARD TO ESP32 COMMUNICATION //////////////////////////////////

void requestEvent() {
  uint16_t temperatureData = (int)round(averageTemperature * 100);
  uint16_t pHData = (int)round(averagePH * 100);
  uint16_t rpmData = (int)round(averageRPM);
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

  // init pH subsystem
  pinMode(PH_SENSOR, INPUT);
  pinMode(ACID_PUMP, OUTPUT);
  pinMode(ALKALI_PUMP, OUTPUT);
}

// Non blocking loop to get the averages of the sensor readings
const int numSamples = 10;
int sensorIndex = 0;
int numRecordedReadings = 0;
static unsigned long lastReadingTime = 0;
int sampleTime = 10;

float pHReadings[numSamples];
float currentpH;
float pHSum = 0;

float temperatureReadings[numSamples];
float currentTemperature;
float temperatureSum = 0;

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastReadingTime >= sampleTime) {
    lastReadingTime = currentMillis;
    
    currentpH = getPH();
    // Serial.print(currentpH);
    // Serial.print(", ");
    // Serial.print("\n");
    pHSum = pHSum - pHReadings[sensorIndex] + currentpH;
    pHReadings[sensorIndex] = currentpH;
    numRecordedReadings++;
    sensorIndex = (sensorIndex + 1) % numSamples;

    if (numRecordedReadings >= 10){
        averagePH = pHSum / numSamples;
        Serial.print("Average pH:" );
        Serial.println(averagePH);
    }

    // controlPH(pH);
    delay(100);
  }
}

