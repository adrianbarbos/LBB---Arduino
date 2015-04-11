// trencadis2 lbbIND 1 - rfid (SoftwareSerial messes up all other LBB stuff - temperature, lights, etc)
// kim        lbbIND 2 - led, temp
// andrei     lbbIND 3 - servo, temp
// Kim        lbbIND 4 - LCD

#include <SoftwareSerial.h>
#include <Ethernet.h>
#include <SPI.h>

// rfid part
SoftwareSerial RFID(A0, A1); // RX and TX
char lastCard[14];

int enumCount = 1;
const char EOPmarker = '.'; //This is the end of packet marker
char serialbuf[32]; //This gives the incoming serial some room. Change it if you want a longer incoming.
#include <string.h> // we'll need this for subString
#define MAX_STRING_LEN 20 // like 3 lines above, change as needed.

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  
  
  
String data;
String dataFinal;
String rfid;
String lastCardFinal;

IPAddress ip(169,254,10,24);


EthernetClient client;

void setup() {
  Ethernet.begin(mac, ip);
  Serial.begin(9600);  
  client
  RFID.begin(9600); // start serial to RFID read
  Serial.println("Starting");
  data = "http://www.gardenandhomemaintenance.co.uk/iot/api/index.php?";
  lastCardFinal = "";
  rfid = "rfid=";
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
      lastCardFinal = lastCardFinal + inchar;
      if (i != 0) { 
        rfidbufpos++; 
      }
    }

    RFID.flush(); // stops multiple reads
    delay(500);
    //Serial.println("DEBUG: I got a card");
  
    data = "rfid=" + lastCardFinal + "&API_KEY=cyAa6pnNvAVtSZyNegGT&METHOD=storeData";
    dataFinal = "http://www.gardenandhomemaintenance.co.uk/iot/api/index.php?" + data;
    Serial.print(dataFinal);

    client.connect("www.gardenandhomemaintenance.co.uk", 80);
    if (client.connected())
    {
      Serial.print("Ceapa");
    }
    delay(500);
    client.println("GET /iot/api/index.php?rfid_id=blabla&API_KEY=cyAa6pnNvAVtSZyNegGT&METHOD=storeData HTTP 1.1");
    client.println("");
//    client.println("Host: www.gardenandhomemaintenance.co.uk");
//    client.println("Content-Type: application/x-form-urlencoded");
//    client.println("Content-length: ");
//    client.println(dataFinal.length());
//    client.print(dataFinal);
    
    
    lastCard[rfidbufpos] = 0;
    rfidbufpos = 0;

  }

  // if serial activity detected  

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





