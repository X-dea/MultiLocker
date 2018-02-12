/*!
   \file config.h
   \brief Configurations of system
   \author Jason C.H
   \date Jan. 2018
*/

#ifndef CONFIG_H
#define CONFIG_H

/**
 * HAL DEFINITION
 * 硬件层定义
 */
#include "HAL_ArduMega328p.h"
//#include "HAL_ArduMega2560.h"

/**
 * HARDWARE WATCHDOG
 * 硬件看门狗
 * Warning: You may need to reburn bootloader to support this function.
 * 警告：您可能需要重新烧写引导程序以支持本功能。
 */
#define USE_HARDWARE_WATCHDOG

/**
 * AUTHTYPE DEFINITION
 * 定义启用的认证类型
 */
#define USE_RC522
//#define USE_LB522
#define USE_R308

/**
 * DATASTORE DEFINITION(ONLY ONE)
 * 定义启用的认证存储（唯一启用）
 */
#define USE_LOCAL

// DISPLAY DEFINITION
// 显示屏相关
#define USE_DISPLAY

/**
 * DISPLAY TYPE DEFINITION
 * 显示类型定义
 * Supported:
 * U8GLIB_SSD1306_128X64
 * LCD12864_IIC
 */
#ifdef USE_DISPLAY
#define DISPLAY_TYPE U8GLIB_SSD1306_128X64
#endif

#endif
