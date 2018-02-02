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
#include "HAL_ArduProMini.h"
//#include "HAL_ArduMega2560.h"

/**
 * HARDWARE WATCHDOG
 * Warning: Only UNO's bootloader support watchdog!
 * 硬件看门狗
 * 警告：只有 UNO 的 bootloader 支持硬件看门狗！
 */
#define USE_HARDWARE_WATCHDOG

/**
 * AUTHTYPE DEFINITION
 * 定义启用的认证类型
 */
//#define USE_RC522
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

// MYSQL DEFINITION
// 启用MYSQL数据库(仅在网络存储启用时可定义)
//#define USE_MYSQL
#ifdef USE_MYSQL
#define MYSQL_ADDRESS MYADDRESS
#define MYSQL_DATABASE MultiLockers
#define MYSQL_PASSWOED MYPASSWORFD
#define MYSQL_TABLE MultiLockers
#endif

#endif
