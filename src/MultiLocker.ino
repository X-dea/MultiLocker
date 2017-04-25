/*
 * MultiLocker (GPLv3)
 * Support by CTBeta Team
 * Created by Jason C.H Feb 2017
 */

#include "config.h"
#include "buzzer.h"

#ifdef USE_RC522
  #include "Link_rc522.h"
  RC522 Rfidauth;
  extern class RFID Rc522;
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
  Serial.begin(57600);
  pinMode(PIN_LOCK,OUTPUT);
  Buzzer.start();
}

void loop() {
  if(digitalRead(PIN_INBUTTON)!=1)
	{
    if (Rfidauth.findcard()) {
      bool temp=Rfidauth.authid();
      bool temp2=Rfidauth.authkey();
      if (temp&&temp2)
        open();
    }
  }else open();
}
