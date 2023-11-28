
#include <Wire.h>

const int ESP_TO_NUCLEO_PORT = 9;
// const int phSensor = ?
// const int temperatureSensor = ?
// const int stirringSensor = ?

void printAvailableFromWire(){
  while (Wire.available()){
    char c = Wire.read();
    Serial.print(c);
  }
}

void receiveEvent(int howMany) {
  Serial.println("\nA message has been received...");

  // To send the sensor values, it is transmitted in chunks of bytes
  byte byte1 = Wire.read();
  byte byte2 = Wire.read();
  int receivedData = (byte1 << 8) | byte2;
  Serial.println(receivedData);
}

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

