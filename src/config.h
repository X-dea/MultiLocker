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
// #include "HAL_ArduMega328p.h"
#include "HAL_ArduMega2560.h"

/**
 * HARDWARE WATCHDOG
 * 硬件看门狗
 * Warning: You may need to reburn bootloader to support this function.
 * 警告：您可能需要重新烧写引导程序以支持本功能。
 */
// #define USE_HARDWARE_WATCHDOG

/**
 * AUTHTYPE DEFINITION
 * 定义启用的认证类型
 */
// #define USE_RC522
// #define USE_LB522
#define USE_R308

/**
 * DATASTORE DEFINITION
 * 定义启用的认证存储位置
 */
// #define USE_LOCAL

/**
 * Configurations for R308 fingerprint module.
 * R308指纹模块相关设置
 */

/**
 * Define user roles.
 * 定义用户组区块
 */
#define kRoleRootMin 1
#define kRoleRootMax 10
#define kRoleSecondMin 11
#define kRoleSecondMax 30
#define kRoleLeaderMin 31
#define kRoleLeaderMax 100
#define kRoleMemberMin 101
#define kRoleMemberMax 500

/**
 * Define latest fingerprint pointer for each role in EEPROM.
 * 在EEPROM中定义存放各用户组最新成员的位置
 * Warning: Latest fingerprint pointers will take 8 bytes [start,start+8) for 4
 * groups in eeprom.
 * 警告：EEPROM中用户组区块信息存储将会占用8字节
 */
#define kFingerprintPointerStart 1

#endif
