/*!
   \file HAL_ArduMega328p.h
   \brief HAL for Arduino Atmega328p based board
   \author Jason C.H
   \date Feb. 2017
*/

#ifndef HAL_ARDUMEGA328P_H
#define HAL_ARDUMEGA328P_H

// I2C PORT
#define PIN_SDA 4
#define PIN_SCL 5

// SPI PIN
#define PIN_MISO 12
#define PIN_MOSI 11
#define PIN_SCK 13
#define PIN_SS 10

// IO
#define PIN_INBUTTON 4 // INDOOR BUTTON
#define PIN_BUZZER 5   // BUZZER
#define PIN_RFID_RST 5 // RFID
#define PIN_LOCK 9     // lOCK
#define PIN_DETECT 3   // Detector

// EEPROM
#define EEPROM_SIZE 1000

#endif
