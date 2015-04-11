// trencadis2 lbbIND 1 - rfid (SoftwareSerial messes up all other LBB stuff - temperature, lights, etc)
// kim        lbbIND 2 - led, temp
// andrei     lbbIND 3 - servo, temp
// Kim        lbbIND 4 - LCD

// rfid part
#include <SoftwareSerial.h>
SoftwareSerial RFID(A0, A1); // RX and TX
char lastCard[14];

// proto part
String enumMethod = "enum";
String getMethod = "get";
String putMethod = "put";
int enumCount = 1;
const char EOPmarker = '.'; //This is the end of packet marker
char serialbuf[32]; //This gives the incoming serial some room. Change it if you want a longer incoming.
#include <string.h> // we'll need this for subString
#define MAX_STRING_LEN 20 // like 3 lines above, change as needed.

void setup() {
  Serial.begin(57600);  
  RFID.begin(9600); // start serial to RFID read
  Serial.println("Starting");
}

void loop() {
  // Get the current ambient temperature in degrees Celsius with a range of -40 C to 87 C.
  //int temperature = Bean.getTemperature();
  
  // if RFID activity detected , build and print lastCard
  if (RFID.available() > 0) {
    static int rfidbufpos = 0; //starts the buffer
    delay(500);
    for (int i = 0 ; i < 13 ; i++) // read the rest of the tag
    {
      char inchar = RFID.read(); // assings one byte
      lastCard[rfidbufpos] = inchar; 
      if (i != 0) { rfidbufpos++; }
    }
    lastCard[rfidbufpos] = 0;
    rfidbufpos = 0;
    RFID.flush(); // stops multiple reads
    delay(500);
    Serial.println("DEBUG: I got a card");
    //Serial.println(lastCard);
  }

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
          Serial.println(enumCount);           // enumerate all sensors
        } 
        else if (argument == 1 ){             //enumerate type of sensors     
          Serial.println("1;R;FIXME;ok");  
        } 
        
//        else if (argument == 2) {
//          Serial.println("2;W;FIXME;ok");
//        } else if (argument == 3) {
//          Serial.println("3;W;FIXME;ok");
//        } else if (argument == 4) {
//          Serial.println("4;W;FIXME;ok");
//        }

      } else if (command == getMethod){         //get
        if (argument == 1) {                    // get card
          Serial.println(lastCard);
        } 
      } 
      
//      else if (command == putMethod){         // put
//        if (argument == 2) {                    // put R
//        //Bean.setLed(255, 0, 0);
//        } else if (argument == 3) {             // put G
//          //Bean.setLed(0, 255, 0);
//        } else if (argument == 4) {             // put B
//          //Bean.setLed(0, 0, 255);
//        }
//      }
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




