#include <Wire.h>

int wireTransmissionChannel = 50;

void setup() {
  Serial.begin(57600);
  Wire.begin();
}

void loop() {
  
  if(Serial.available()) {
      char ch = Serial.read();
      sendWireChar(ch);  
  }

}

void sendWireChar(char ch) {
  Wire.beginTransmission(wireTransmissionChannel);
  Wire.write(ch);
  Wire.endTransmission();
}
