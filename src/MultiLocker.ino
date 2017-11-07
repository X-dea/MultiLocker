/*!
   \file MultiLocker.ino
   \brief A opensource lock framework based on Arduino.
   \author Jason C.H
   \date Feb. 2017
*/

#include "MultiLocker.h"

// Initialize buzzer
//初始化蜂鸣器
buzzer Buzzer;

// Open Lock Function
//开锁函数
void open() {
  Buzzer.open();
  digitalWrite(PIN_LOCK, HIGH);
  delay(2000);
  digitalWrite(PIN_LOCK, LOW);
}

// Setup Mode
//设定模式
void setupMode() {
// Buzzer.setupMode();

#ifdef USE_R308
  FP.setupMode();
#endif

  for (;;) {
  }
}

// Main
//主程序
void setup() {
  pinMode(PIN_LOCK, OUTPUT);

  if (digitalRead(PIN_INBUTTON) == HIGH) {
    unsigned int timestart = millis();
    while (digitalRead(PIN_INBUTTON) == HIGH) {
      if ((millis() - timestart) >= 10000)
        setupMode();
    }
  }

  Buzzer.start();
}

void loop() {

  if (digitalRead(PIN_INBUTTON) == HIGH)
    open();

#ifdef USE_RC522
  if (Rfid.findCard()) {
    bool temp = Rfid.authId();
    bool temp2 = Rfid.authKey();
    if (temp && temp2)
      open();
  }
#endif

#ifdef USE_R308
  if (digitalRead(PIN_DETECT) == LOW) {
    delay(300);
    r308.init();
    if (FP.searchFinger() == true)
      open();
  }
#endif
}
