/*!
   \file HAL_ArduMega2560.h
   \brief HAL for Arduino Mega 2560
   \author Jason C.H
   \date Feb. 2017
*/

#ifndef HAL_ARDUMEGA2560_H
#define HAL_ARDUMEGA2560_H

// I2C PORT
#define PIN_SDA 20
#define PIN_SCL 21

// SPI PIN
#define PIN_MISO 50
#define PIN_MOSI 51
#define PIN_SCK 52
#define PIN_SS 53

// IO
#define PIN_INBUTTON 3 // INDOOR BUTTON
#define PIN_BUZZER 5   // BUZZER
#define PIN_RFID_RST 5 // RFID
#define PIN_LOCK 9     // lOCK
#define PIN_DETECT 4   // Detector

// EEPROM
#define EEPROM_SIZE 4000

#endif
