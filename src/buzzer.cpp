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

uint16_t buzzer::startNote[] = {M3, M4, M5, M6};
uint16_t buzzer::openNote[] = {H3};

buzzer::buzzer() { pinMode(PIN_BUZZER, OUTPUT); }

void buzzer::start() { playNote(startNote, 4); }
void buzzer::open() { playNote(openNote, 1); }

/*!
   \brief Play note.
   \brief 播放音符
   \param uint16_t* note(音符)/uint16_t noteLength(长度)
*/
void buzzer::playNote(uint16_t *note, uint16_t noteLength) {
  for (uint16_t i = 0; i <= noteLength; i++) {
    tone(PIN_BUZZER, note[i]);
    delay(120);
    noTone(PIN_BUZZER);
    delay(20);
  }
}
