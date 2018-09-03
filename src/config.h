/*!
   \file config.h
   \brief Configurations of system
   \author Jason C.H
   \date Jan. 2018
*/

#ifndef CONFIG_H
#define CONFIG_H

/********************
 * Compile configuration
 * 编译设定
 */

/**
 * Debug mode
 * 调试模式
 * This mode will print extra debug informations to the debug serial port
 * 这一模式将在调试串口输出额外的调试信息
 */
#define ENABLE_DEBUG_MODE
#define debugSerPort Serial

/********************
 * Compile configuration
 * 编译设定
 */

/**
 * IO definition
 * 硬件接口定义
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

/********************
 * Configurations for R308 fingerprint module
 * R308指纹模块相关设置
 */

/**
 * Define location range of roles
 * 定义用户组区块位置
 */
#define kRoleRootMin 1
#define kRoleRootMax 10
#define kRoleSecondMin 11
#define kRoleSecondMax 30
#define kRoleThirdMin 31
#define kRoleThirdMax 100
#define kRoleFourthMin 101
#define kRoleFourthMax 500

/**
 * Define latest fingerprint pointer for each role in EEPROM.
 * 在EEPROM中定义存放各用户组最新成员的位置
 * Warning: Latest fingerprint pointers will take 8 bytes [start,start+8) for 4
 * groups in eeprom.
 * 警告：EEPROM中用户组区块信息存储将会占用8字节
 */
#define kFingerprintPointerStart 1

#endif
