// generic code to run on all lbbs

// kim        lbbIND 2 - temp(R) red(W), green(W), blue(W)
// Kim        lbbIND 3 - temp(R) red(W), green(W), blue(W)
// Andrei     lbbIND 4 - temp(R) red(W), green(W), blue(W)

// id and sensors def
int enumCount = 4;
int lbbId = 4;

// proto stuff
String idMethod = "lbbId";
String enumMethod = "enum";
String getMethod = "get";
String putMethod = "put";
const char EOPmarker = '.'; //This is the end of packet marker
char serialbuf[32]; //This gives the incoming serial some room. Change it if you want a longer incoming.
#include <string.h> // we'll need this for subString
#define MAX_STRING_LEN 20 // like 3 lines above, change as needed.

void setup() {
  Serial.begin(57600); 
  pinMode(0,OUTPUT);
}

void loop() {
  // Get the current ambient temperature in degrees Celsius with a range of -40 C to 87 C.
  int temperature = Bean.getTemperature();

  // if serial activity detected
  if (Serial.available() > 0) { 
    static int bufpos = 0; //starts the buffer
    char inchar = Serial.read(); //assigns one byte  
    if (inchar != EOPmarker) { 
      serialbuf[bufpos] = inchar; 
      bufpos++; 
    }
    else { //once the end of package marker has been read
      serialbuf[bufpos] = 0; //restart the buff
      bufpos = 0; //restart the position of the buff

      //check whats up in serialbuf
      String command = subStr(serialbuf, " ", 1);
      int argument = atoi(subStr(serialbuf, " ", 2));
      int value = atoi(subStr(serialbuf, " ", 3));

      if (command == enumMethod){
        if (argument == NULL){
          Serial.print(enumCount);           // enumerate all sensors
        } 
        else if (argument == 1 ){             //enumerate type of sensors     
          Serial.print("1;R;FIXME;ok");  
        } 
        else if (argument == 2) {
          Serial.print("2;W;FIXME;ok");
        } 
        else if (argument == 3) {
          Serial.print("3;W;FIXME;ok");
        } 
        else if (argument == 4) {
          Serial.print("4;W;FIXME;ok");
        }
      } 
      else if (command == getMethod){         //get
        if (argument == 1) {                    // get temp
          Serial.print(temperature);
        } 
      } 

      else if (command == putMethod){           // put
        if (argument == 2) {                    // put R
          Bean.setLed(value, 0, 0);
        } 
        else if (argument == 3) {             // put G
          Bean.setLed(0, value, 0);
        } 
        else if (argument == 4) {             // put B
          Bean.setLed(0, 0, value);
        } 
      }
      
      else if (command == idMethod) {
         Serial.print(lbbId);
      }
      
    }
  }
}


char* subStr (char* input_string, char *separator, int segment_number) {
  char *act, *sub, *ptr;
  static char copy[MAX_STRING_LEN];
  int i;
  strcpy(copy, input_string);
  for (i = 1, act = copy; i <= segment_number; i++, act = NULL) {
    sub = strtok_r(act, separator, &ptr);
    if (sub == NULL) break;
  }
  return sub;
}





