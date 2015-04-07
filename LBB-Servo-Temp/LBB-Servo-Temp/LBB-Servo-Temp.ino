#include <Servo.h>

int sensorPin = 0;
int servoPin = 0;
int redLedPin = 1;

Servo servo;

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

void setup() {
  Serial.begin(57600);
  servo.attach(servoPin); //Attach servo to servoPin
  pinMode(redLedPin, OUTPUT);
}

void loop() {
    if(Serial.available()) {
        String str = Serial.readString();
        serialAction(str);
    }
}

void serialAction(String str) {
  
  String option = getValue(str, ';', 0);
  String angleString = getValue(str, ';', 1);
  int angle = angleString.toInt();
  Serial.println("Option " + option);
  Serial.println("Angle " + angleString);

  if (option == "1") {
    writeServo(angle);
    digitalWrite(redLedPin, HIGH);
  }
  if (option == "2") {
    digitalWrite(redLedPin, LOW);
    Serial.println("Current Servo Position: ");
    Serial.print(readServo());    
  }
  if (option == "3") {
    
        int reading = analogRead(sensorPin);  
     
       // converting that reading to voltage, for 3.3v arduino use 3.3
       float voltage = reading * 5.0;
       voltage /= 1024.0; 
       
       // print out the voltage
       //Serial.print(voltage); Serial.println(" volts");
       
       // now print out the temperature
       float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                     //to degrees ((voltage - 500mV) times 100)
       Serial.print(temperatureC); Serial.println(" degrees C");
       
       // now convert to Fahrenheit
       //float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
       //Serial.print(temperatureF); Serial.println(" degrees F");
       
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
