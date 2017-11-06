/*!
   \file buzzer.cpp
   \brief Buzzer controller
   \author Jason C.H
   \date Nov. 2016

   A controller of buzzer.<br />
   一个蜂鸣器控制器。
*/

#include "buzzer.h"
#include "config.h"

unsigned short buzzer::startNote[] = {M3, M4, M5, M6};
unsigned short buzzer::openNote[] = {H3};

buzzer::buzzer() { pinMode(PIN_BUZZER, OUTPUT); }

// Buzzer when start
void buzzer::start() { playNote(startNote, 4); }

// Buzzer when open
void buzzer::open() { playNote(openNote, 1); }

void buzzer::playNote(unsigned short note[], unsigned short noteLength) {
  for (uint8_t i = 0; i <= noteLength; i++) {
    tone(PIN_BUZZER, note[i]);
    delay(120);
    noTone(PIN_BUZZER);
    delay(20);
  }
}
