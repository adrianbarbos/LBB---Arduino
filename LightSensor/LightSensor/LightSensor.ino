#define LIGHT_PIN A0
int  LightValue; 
int redLightPin = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LIGHT_PIN, INPUT); 
  pinMode(redLightPin, OUTPUT); // Not really necessary: here for example
  Serial.begin(9600);          // Enable the Serial data output
  Serial.println("YourDuino Light Sensor Test 1.00 ");
}

void loop() {
  LightValue = analogRead(LIGHT_PIN);  //Read the voltage from sensor
  Serial.println(LightValue,DEC); 
  if(LightValue < 150) {
    digitalWrite(redLightPin, HIGH);
  } else {
    digitalWrite(redLightPin, LOW);
  }  // Send result to Serial Monitor
  delay(500);
  
  
  
}
