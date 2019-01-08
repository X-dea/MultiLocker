/*!
   \file MultiLocker.ino
   \brief A opensource lock framework based on Arduino.
   \author Jason C.H
   \date Feb. 2017
*/

#include "MultiLocker.h"

// Open Lock Function
// 开锁函数
void open() {
  Buzzer::Open();
  digitalWrite(PIN_LOCK, HIGH);
  delay(2000);
  digitalWrite(PIN_LOCK, LOW);
  Buzzer::Close();
}

/**
 * Setup mode.
 * 设定模式
 */
void setupMode() {
  Buzzer::Setup();
#ifdef USE_R308
  r308.SetupMode();
#endif
  for (;;) {
  }
}

void setup() {
  // Initialize buzzer.初始化蜂鸣器
  Buzzer::Init();

  pinMode(PIN_LOCK, OUTPUT);
  pinMode(PIN_INBUTTON, INPUT);

  if (digitalRead(PIN_INBUTTON) == HIGH) setupMode();

  Buzzer::Start();

// Register hardware watchdog.注册硬件看门狗
#ifdef USE_HARDWARE_WATCHDOG
  wdt_enable(WDTO_8S);
#endif
}

void loop() {
  if (digitalRead(PIN_INBUTTON) == HIGH) open();

#ifdef USE_RC522
  if (Rfid.findCard()) {
    bool temp = Rfid.authId();
    bool temp2 = Rfid.authKey();
    if (temp) open();
  }
#endif

#ifdef USE_R308
  if (digitalRead(PIN_DETECT) == LOW) {
    delay(300);
    r308.Init();
    if (r308.Auth(r308.GetUser(), kAllRole) == true) open();
  }
#endif

#ifdef USE_HARDWARE_WATCHDOG
  wdt_reset();
#endif
}
