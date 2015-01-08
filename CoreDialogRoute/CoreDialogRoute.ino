#include <CoreDialog.h>

#define MY_ADDRESS 9

int address = MY_ADDRESS;

CoreDialog RV; // obiekt receivera

CoreDialog SD1; // obiekt pierwszego portu nadajacego
CoreDialog SD2;
CoreDialog OR;


struct RECEIVE_DATA_STRUCTURE{
  int blinks;
  int pause;
  int address;
  int ttl;
  int global_command;
  int command;
  int registry;



};


RECEIVE_DATA_STRUCTURE mydata;


struct ORIGIN_DATA_STRUCTURE{
  int blinks;
  int pause;
  int address;
  int ttl;
  int global_command;
  int command;
  int registry;



};


ORIGIN_DATA_STRUCTURE origindata;

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  
  
  RV.begin(details(mydata), &Serial1); 
  OR.begin(details(origindata), &Serial1); 
  
  SD1.begin(details(mydata), &Serial2); 
  SD2.begin(details(mydata), &Serial3); 
  
  
  pinMode(9, OUTPUT);
  
}

void loop(){

 
  
  if(RV.receiveData()){
       if (mydata.ttl>0) {
       mydata.ttl--;
       SD2.sendData();
       SD1.sendData();
       }
       

     
    if(address==mydata.address) { // alternatywnie moze byc inny warunek, np grupy
    
      origindata.address = 0;
      origindata.ttl = 10;
      origindata.blinks = 3;
      origindata.pause = 1;
      
      OR.sendData();
    

      Serial.println("d");
       for(int i = mydata.blinks; i>0; i--){
      digitalWrite(9, HIGH);
      delay(mydata.pause * 100);
      digitalWrite(9, LOW);
      delay(mydata.pause * 100);
    }
  
    }

   if(SD1.receiveData()){
       if (mydata.ttl>0) {
       mydata.ttl--;
       RV.sendData();
       
       }
       
   }
       
     if(SD2.receiveData()){
       if (mydata.ttl>0) {
       mydata.ttl--;
       RV.sendData();
       
       }
       
     }
       


    }


  // ten delay musi byc krotki
  delay(2);
  
  
  }
  



