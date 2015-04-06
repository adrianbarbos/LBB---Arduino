#include <Wire.h>

int wireTransmissionChannel = 50;

void setup() {
  Wire.begin(wireTransmissionChannel);
  Wire.onReceive(receiveEvent);
  Serial.begin(57600);
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

void receiveEvent(int howMany)
{
  Serial.println("LBB response test");
}
