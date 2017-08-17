/**
* MultiLocker (GPLv3)
* Support by CTBeta Team http://ctbeta.org/
* Created by Jason C.H Feb 2017
*/

#include <Arduino.h>
#include "Config.h"
#include "buzzer.h"

//TUNE DEFINITION
//定义音调
int starttune[]={
  M3,M4,M5,M6
};
int opentune[]={
  H3
};

buzzer::buzzer(){
  pinMode(PIN_BUZZER,OUTPUT);
}

//Buzzer when start
void buzzer::start(){
  int length=sizeof(starttune)/sizeof(starttune[0]);
  for(int i=0;i<=length;i++){
    tone(PIN_BUZZER,starttune[i]);
    delay(120);
    noTone(PIN_BUZZER);
    delay(20);
  }
}

//Buzzer when open
void buzzer::open(){
  int length=sizeof(opentune)/sizeof(opentune[0]);
  for(int i=0;i<=length;i++){
    tone(PIN_BUZZER,opentune[i]);
    delay(120);
    noTone(PIN_BUZZER);
    delay(20);
  }
}
