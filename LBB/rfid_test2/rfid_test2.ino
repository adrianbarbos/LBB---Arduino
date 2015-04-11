#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>

// eth shield part
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "www.gardenandhomemaintenance.co.uk";    // name address for Google (using DNS)
IPAddress ip(192,168,0,177);
EthernetClient client;
String lastCardFinal;

// rfid part
SoftwareSerial RFID(A0, A1); // RX and TX
char lastCard[14];
int enumCount = 1;
const char EOPmarker = '.'; //This is the end of packet marker
char serialbuf[32]; //This gives the incoming serial some room. Change it if you want a longer incoming.
#include <string.h> // we'll need this for subString
#define MAX_STRING_LEN 20 // like 3 lines above, change as needed.

void setup() {
  Serial.begin(9600);
  RFID.begin(9600); // start serial to RFID read
}

void loop()
{
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
    RFID.flush(); // stops multiple read

    lastCardFinal.remove(0,1);
    connection(lastCardFinal);
    
    // if there are incoming bytes available 
    // from the server, read them and print them:
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }

    // if the server's disconnected, stop the client:
    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting.");
      client.stop();
    }

    lastCard[rfidbufpos] = 0;
    rfidbufpos = 0;
  }



}

void connection(String str)
{
  Serial.print(str);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  Serial.println("connecting...");
  delay(1000);
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /iot/api/index.php?rfid_id=" + str + "&API_KEY=cyAa6pnNvAVtSZyNegGT&METHOD=storeData HTTP/1.0");
    Serial.println("GET /iot/api/index.php?rfid_id=" + str + "&API_KEY=cyAa6pnNvAVtSZyNegGT&METHOD=storeData HTTP/1.0");
    client.println("Host: www.gardenandhomemaintenance.co.uk");
    client.println("Connection: close");
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  delay(1000);
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

