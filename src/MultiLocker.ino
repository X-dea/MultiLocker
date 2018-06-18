/*!
   \file MultiLocker.ino
   \brief A opensource lock framework based on Arduino.
   \author Jason C.H
   \date Feb. 2017
*/

#include "MultiLocker.h"

// Initialize buzzer
// 初始化蜂鸣器
Buzzer buzzer;

// Open Lock Function
// 开锁函数
void open() {
  buzzer.open();
  digitalWrite(PIN_LOCK, HIGH);
  delay(2000);
  digitalWrite(PIN_LOCK, LOW);
  buzzer.close();
}

// Setup Mode
// 设定模式
void setupMode() {}

// Main
// 主程序
void setup() {
  pinMode(PIN_LOCK, OUTPUT);
  pinMode(PIN_INBUTTON, INPUT);

  if (digitalRead(PIN_INBUTTON) == HIGH) {
    unsigned int timestart = millis();
    while (digitalRead(PIN_INBUTTON) == HIGH) {
      if ((millis() - timestart) >= 10000)
        setupMode();
    }
  }

  buzzer.start();

#ifdef USE_HARDWARE_WATCHDOG
  wdt_enable(WDTO_8S);
#endif
}

void loop() {
  if (digitalRead(PIN_INBUTTON) == HIGH)
    open();

#ifdef USE_RC522
  if (Rfid.findCard()) {
    bool temp = Rfid.authId();
    bool temp2 = Rfid.authKey();
    if (temp)
      open();
  }
#endif

#ifdef USE_R308
  if (digitalRead(PIN_DETECT) == LOW) {
    delay(300);
    r308.init();
    if (FP.readAndSearch() == true)
      open();
  }
#endif

#ifdef USE_HARDWARE_WATCHDOG
  wdt_reset();
#endif
}
