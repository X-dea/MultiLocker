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

// Initialize Auth Module
//初始化认证模块
#ifdef USE_RC522
#include "link_rc522.h"
RC522 Rfid;
extern class RFID Rc522;
#endif

#ifdef USE_R308
#include "link_r308.h"
#include <CTB_R308.h>
LR308 FP;
extern class R308_act r308;
#endif

#endif