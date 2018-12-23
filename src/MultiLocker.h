/*!
   \file MultiLocker.h
   \brief A opensource lock framework based on Arduino.
   \author Jason C.H
   \date Feb. 2017
*/

#ifndef MULTILOCKER_H
#define MULTILOCKER_H

#include "buzzer.h"
#include "config.h"

// Hardware Watchdog
#ifdef USE_HARDWARE_WATCHDOG
#include <avr/wdt.h>
#endif

// Initialize Auth Module
#ifdef USE_RC522
#include "link_rc522.h"
RC522 Rfid;
extern class RFID rc522;
#endif

#ifdef USE_R308
#include <r308.h>
#include "linker_r308.h"
R308Linker FP;
extern class R308 r308;
#endif

#endif
