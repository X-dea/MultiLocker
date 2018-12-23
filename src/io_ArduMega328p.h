/**
 * @file io_ArduMega328p.h
 * @author Jason C.H
 * @brief IO defination for Arduino Atmega328p based board.
 * @date 2018-12-23
 */

#ifndef HAL_ARDUMEGA328P_H
#define HAL_ARDUMEGA328P_H

// I2C Port
#define PIN_SDA 4
#define PIN_SCL 5

// SPI Pin
#define PIN_MISO 12
#define PIN_MOSI 11
#define PIN_SCK 13
#define PIN_SS 10

// IO
#define PIN_INBUTTON 4  // Indoor button
#define PIN_BUZZER 5    // Buzzer
#define PIN_LOCK 9      // Lock
#define PIN_DETECT 3    // Detector

// RC522
#define PIN_RC522_RST 5  // RFID RST

// EEPROM
#define EEPROM_SIZE 1000

#endif
