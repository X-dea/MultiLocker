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

void Buzzer::Init() { pinMode(PIN_BUZZER, OUTPUT); }
void Buzzer::Start() { PlayNote(startNote, 4); }
void Buzzer::Open() { PlayNote(openNote, 2); }
void Buzzer::Close() { PlayNote(closeNote, 2); }
void Buzzer::Setup() { PlayNote(setupNote, 4); }

/**
 * @brief Play note
 *
 * @param note 音符
 * @param length 长度
 */
void Buzzer::PlayNote(const uint16_t *note, uint16_t length) {
  for (uint16_t i = 0; i <= length - 1; i++) {
    tone(PIN_BUZZER, note[i]);
    delay(120);
    noTone(PIN_BUZZER);
    delay(20);
  }
}
