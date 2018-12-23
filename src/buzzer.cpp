/**
 * @file buzzer.cpp
 * @author Jason C.H
 * @brief Controller of buzzer.

 * @date 2018-12-23
 */

#include "buzzer.h"

const uint16_t Buzzer::startNote[] = {M3, M4, M5, M6};
const uint16_t Buzzer::openNote[] = {H3, H4};
const uint16_t Buzzer::closeNote[] = {H4, H3};
const uint16_t Buzzer::setupNote[] = {M3, M4, M5, M5};

Buzzer::Buzzer() { pinMode(PIN_BUZZER, OUTPUT); }

void Buzzer::start() { playNote(startNote, 4); }
void Buzzer::open() { playNote(openNote, 2); }
void Buzzer::close() { playNote(closeNote, 2); }
void Buzzer::setup() { playNote(setupNote, 4); }

/**
 * @brief Play note
 *
 * @param note 音符
 * @param length 长度
 */
void Buzzer::playNote(const uint16_t *note, uint16_t length) {
  for (uint16_t i = 0; i <= length - 1; i++) {
    tone(PIN_BUZZER, note[i]);
    delay(120);
    noTone(PIN_BUZZER);
    delay(20);
  }
}
