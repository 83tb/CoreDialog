#include <CoreDialog.h>


CoreDialog ET; 
CoreDialog ET2; 



struct SEND_DATA_STRUCTURE{
 
  int blinks;
  int pause;
  int address;
  int ttl;
  int global_command;
  int command;
  int registry;



};


SEND_DATA_STRUCTURE mydata;



void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  ET.begin(details(mydata), &Serial1);
  ET2.begin(details(mydata), &Serial2);
 
  

  
  
  pinMode(9, OUTPUT);
  
  randomSeed(analogRead(0));
  
}

void loop(){
  
  mydata.blinks = 2;
  mydata.pause = 0;
  mydata.address = 9;
  mydata.ttl = 10;
  
  ET.sendData();
  ET2.sendData();
  
   if(ET.receiveData()){
  
   for(int i = mydata.blinks; i>0; i--){
      digitalWrite(9, HIGH);
      delay(mydata.pause * 100);
      digitalWrite(9, LOW);
      delay(mydata.pause * 100);
    }
   }
  
  delay(5000);
}
