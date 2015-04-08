String lbbIDMethod = "lbbId";
int lbbIND = 1;
String enumMethod = "enum";
int enumCount = 5;
String enumStr[]= {"enum1", "enum2", "enum3", "enum4", "enum5"};
String enumVal[]= {"1;R", "2;R", "3;R", "4;W", "5;W"};

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
