// trencadis2 lbbIND 1 - rfid, temp
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
int enumCount = 2;
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
  // if RFID activity detected , build and print lastCard
  if (RFID.available() > 0) {
    static int rfidbufpos = 0; //starts the buffer
    delay(200);
    for (int i = 0 ; i < 13 ; i++) // read the rest of the tag
    {
      char inchar = RFID.read(); // assings one byte
      lastCard[rfidbufpos] = inchar;
      rfidbufpos++;
    }
    lastCard[rfidbufpos] = 0;
    rfidbufpos = 0;
    RFID.flush(); // stops multiple reads
    delay(200);
    Serial.println("DEBUG: I got a card");
    Serial.println(lastCard);
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

      if (command == enumMethod){
        if (argument == NULL){
          Serial.println(enumCount);
        } 
        else {
          Serial.println("FIXME;R;100;ok");
        }
      } else if (command == getMethod){
        if (argument == 1) {
          Serial.println(lastCard);
        }
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




