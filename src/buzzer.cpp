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

uint16_t Buzzer::startNote[] = {M3, M4, M5, M6};
uint16_t Buzzer::openNote[] = {H3, H4};
uint16_t Buzzer::closeNote[] = {H4, H3};
uint16_t Buzzer::pressNote[] = {H2};

Buzzer::Buzzer() { pinMode(PIN_BUZZER, OUTPUT); }

void Buzzer::start() { playNote(startNote, 4); }
void Buzzer::open() { playNote(openNote, 2); }
void Buzzer::close() { playNote(closeNote, 2); }
void Buzzer::press() { playNote(pressNote, 1); }

/*!
   \brief Play note.
   \brief 播放音符
   \param uint16_t* note(音符)/uint16_t noteLength(长度)
*/
void Buzzer::playNote(uint16_t *note, uint16_t noteLength) {
  for (uint16_t i = 0; i <= noteLength-1; i++) {
    tone(PIN_BUZZER, note[i]);
    delay(120);
    noTone(PIN_BUZZER);
    delay(20);
  }
}
