/**
 * @file io_ArduMega2560.h
 * @author Jason C.H
 * @brief IO defination for Arduino Atmega2560 based board.
 * @date 2018-12-23
 */

#ifndef HAL_ARDUMEGA2560_H
#define HAL_ARDUMEGA2560_H

// I2C Port
#define PIN_SDA 20
#define PIN_SCL 21

// SPI Pin
#define PIN_MISO 50
#define PIN_MOSI 51
#define PIN_SCK 52
#define PIN_SS 53

// IO
#define PIN_INBUTTON 3  // Indoor button
#define PIN_BUZZER 5    // Buzzer
#define PIN_LOCK 9      // Lock
#define PIN_DETECT 4    // Detector

// RC522
#define PIN_RC522_RST 5  // RFID RST

// EEPROM
#define EEPROM_SIZE 4000

#endif
