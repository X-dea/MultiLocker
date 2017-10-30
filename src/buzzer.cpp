/**
* MultiLocker (GPLv3)
* Support by CTBeta Team http://ctbeta.org/
* Created by Jason C.H Feb 2017
*/

#include "buzzer.h"
#include "config.h"
#include <Arduino.h>

// TUNE DEFINITION
//定义音调
int startTune[] = {M3, M4, M5, M6};
int setupModeTune[] = {M3, M4, M4, M4};
int openTune[] = {H3};

buzzer::buzzer() { pinMode(PIN_BUZZER, OUTPUT); }

// Buzzer when start
void buzzer::start() {
  int length = sizeof(startTune) / sizeof(startTune[0]);
  for (int i = 0; i <= length; i++) {
    tone(PIN_BUZZER, startTune[i]);
    delay(120);
    noTone(PIN_BUZZER);
    delay(20);
  }
}

void buzzer::setupMode() {
  int length = sizeof(setupModeTune) / sizeof(setupModeTune[0]);
  for (int i = 0; i <= length; i++) {
    tone(PIN_BUZZER, setupModeTune[i]);
    delay(120);
    noTone(PIN_BUZZER);
    delay(20);
  }
}

// Buzzer when open
void buzzer::open() {
  int length = sizeof(openTune) / sizeof(openTune[0]);
  for (int i = 0; i <= length; i++) {
    tone(PIN_BUZZER, openTune[i]);
    delay(120);
    noTone(PIN_BUZZER);
    delay(20);
  }
}
