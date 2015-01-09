#include <CoreDialog.h>


// This sketch is only for testing purposes, do not use it.

CoreDialog ET;

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

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);

  ET.begin(details(mydata), &Serial1);
  pinMode(9, OUTPUT);

}

void loop(){

  if(ET.receiveData()){
    for(int i = mydata.blinks; i>0; i--){
      digitalWrite(9, HIGH);
      delay(mydata.pause * 100);
      digitalWrite(9, LOW);
      delay(mydata.pause * 100);
    }
  }



  // ten delay musi byc krotki
  delay(250);
}
