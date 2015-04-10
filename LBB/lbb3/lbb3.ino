// trencadis2 lbbIND 1 - rfid, temp
// kim        lbbIND 2 - led, temp
// andrei     lbbIND 3 - servo, temp
// Kim        lbbIND 4 - LCD

String lbbIDMethod = "lbbId";
int lbbIND = 1;
String enumMethod = "enum";
int enumCount = 5;
String enumStr[]= {"enum0", "enum1", "enum2", "enum3", "enum4"};
String enumVal[]= {"1;R;100;ok", "2;R;100;ok", "3;R;100;ok", "4;W;ok", "5;W;ok"};

void setup() {
  
  Serial.begin(57600);

}

void loop() {
  
  if(Serial.available()) {
  
    String str = Serial.readString();
    
    if(str == lbbIDMethod){
      Serial.print(String(lbbIND));
    }
    
    if(str == enumMethod){
      Serial.print(String(enumCount));
    }
    
    if(str == enumStr[0]){
      Serial.print(enumVal[0]);
    }
    
    if(str == enumStr[1]){
      Serial.print(enumVal[1]);
    }
    
    if(str == enumStr[2]){
      Serial.print(enumVal[2]);
    }
    
    if(str == enumStr[3]){
      Serial.print(enumVal[3]);
    }
    
    if(str == enumStr[4]){
      Serial.print(enumVal[4]);
    }
  
  }

}
