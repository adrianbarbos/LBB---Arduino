String enumMethod = "enum";
int enumCount = 5;
String enumStr[]= {"enum1", "enum2", "enum3", "enum4", "enum5"};
String enumVal[]= {"1;R", "2;R", "3;R", "4;W", "5;W"};

void setup() {
  
  Serial.begin(9600);

}

void loop() {
  
  if(Serial.available()) {
  
    String str = Serial.readString();
    
    if(str == enumMethod){
      Serial.println(String(enumCount));
    }
    
    if(str == enumStr[0]){
      Serial.println(enumVal[0]);
    }
    
    if(str == enumStr[1]){
      Serial.println(enumVal[1]);
    }
    
    if(str == enumStr[2]){
      Serial.println(enumVal[2]);
    }
    
    if(str == enumStr[3]){
      Serial.println(enumVal[3]);
    }
    
    if(str == enumStr[4]){
      Serial.println(enumVal[4]);
    }
  
  }

}
