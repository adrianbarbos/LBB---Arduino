#include <SoftwareSerial.h>

SoftwareSerial RFID(A0, A1); // RX and TX

int i;

void setup()

{
  RFID.begin(9600); // start serial to RFID read
  Serial.begin(9600);  // start serial to PC

  Serial.print("HelloWorld");

}


void loop()

{

  if (RFID.available() > 0)

  {

    //Serial.print(“HelloWorld3″);

    i = RFID.read();

    Serial.print(i, DEC);

    Serial.print(" ");

  }

}

