/**
 * @file buzzer.h
 * @author Jason C.H
 * @brief Controller of buzzer.

 * @date 2018-12-23
 */

#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "config.h"

// Tune definition.定义音调
#define D0 -1
#define D1 262
#define D2 293
#define D3 329
#define D4 349
#define D5 392
#define D6 440
#define D7 494

#define M1 523
#define M2 586
#define M3 658
#define M4 697
#define M5 783
#define M6 879
#define M7 987

#define H1 1045
#define H2 1171
#define H3 1316
#define H4 1393
#define H5 1563
#define H6 1755
#define H7 1971

class Buzzer {
 private:
  static const uint16_t startNote[4];
  static const uint16_t openNote[2];
  static const uint16_t closeNote[2];
  static const uint16_t setupNote[4];

 public:
  Buzzer();

  void Start();
  void Open();
  void Close();
  void Setup();

  /**
   * @brief Play note
   *
   * @param note 音符
   * @param length 长度
   */
  void PlayNote(const uint16_t *note, uint16_t length);
};

#endif
