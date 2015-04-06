#include <Wire.h>
#include <Servo.h>

int servoPin = 9; //Servo pin
int redLedPin = 12; // Led Pin
int sensorPin = 0;
Servo servo;
int wireTransmissionChannel = 50;

//String Split Method------------------------------------------------------------------------------------------------------------------------------------------

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {
    0, -1
  };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

//Start Setup------------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
  Wire.begin(wireTransmissionChannel);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(redLedPin, OUTPUT);
}

void loop() {}

//Wire receiver methods------------------------------------------------------------------------------------------------------------------------------------------

String receiverWireString;

void receiveEvent(int howMany)
{
  char ch = Wire.read();
  //Serial.println(ch);
  constructWireString(ch);

}

void constructWireString(char ch) {
  if (ch != '$') {
    receiverWireString += String(ch);
  } else {
    Serial.println(receiverWireString);
    wireAction();
    receiverWireString = "";
  }
}

void wireAction() {
  String option = getValue(receiverWireString, ';', 0);
  String angleString = getValue(receiverWireString, ';', 1);
  int angle = angleString.toInt();
  Serial.println("Option " + option);
  Serial.println("Angle " + angleString);

  if (option == "1") {
    writeServo(angle);
    digitalWrite(redLedPin, HIGH);
    //Wire.beginTransmission(50);
    //Wire.write(0);
    //Wire.endTransmission();
  }
  if (option == "2") {
    digitalWrite(redLedPin, LOW);
    Serial.print("Current Servo Position: ");
    Serial.println(readServo());
  }
  if (option == "3") {
    
        int reading = analogRead(sensorPin);  
     
       // converting that reading to voltage, for 3.3v arduino use 3.3
       float voltage = reading * 5.0;
       voltage /= 1024.0; 
       
       // print out the voltage
       Serial.print(voltage); Serial.println(" volts");
       
       // now print out the temperature
       float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                     //to degrees ((voltage - 500mV) times 100)
       Serial.print(temperatureC); Serial.println(" degrees C");
       
       // now convert to Fahrenheit
       float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
       Serial.print(temperatureF); Serial.println(" degrees F");
       
       delay(1000); 
    
  }
}


//Servo methods------------------------------------------------------------------------------------------------------------------------------------------

int readServo() {
  return servo.read();
}

void writeServo(int angle) {

  //servo.attach(servoPin);
  servo.write(angle);
  //servo.writeMicroseconds(1000000);
  delay(1000);
  //servo.detach();
}
