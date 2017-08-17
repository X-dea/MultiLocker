/**
* MultiLocker (GPLv3)
* Support by CTBeta Team http://ctbeta.org/
* Created by Jason C.H Feb 2017
*/

#include "Config.h"
#include "buzzer.h"

#ifdef USE_DISPLAY

#endif

#ifdef USE_RC522
  #include "Link_rc522.h"
  RC522 Rfidauth;
  extern class RFID Rc522;
#endif

#ifdef USE_R308
  #include "Link_r308.h"
  R308 FPauth;
  extern class CTB_R308 R308;
#endif

//初始化蜂鸣器
buzzer Buzzer;

void open(){
	Buzzer.open();
	digitalWrite(PIN_LOCK,HIGH);
	delay(2000);
  digitalWrite(PIN_LOCK,LOW);
}

void setup() {
  pinMode(PIN_LOCK,OUTPUT);
  Buzzer.start();
}

void loop() {
  if(digitalRead(PIN_INBUTTON)!=1)
	{
    if (Rfidauth.findCard()) {
      bool temp=Rfidauth.authId();
      bool temp2=Rfidauth.authKey();
      if (temp&&temp2)
        open();
    }
  }else open();
}
