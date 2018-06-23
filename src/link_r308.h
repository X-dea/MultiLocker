/*!
   \file link_r308.cpp
   \brief Linker for R308 Module
   \author Jason C.H
   \date Feb. 2018
*/

#ifndef LINK_R308_H
#define LINK_R308_H

#include <Arduino.h>

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

class R308Linker {
private:
  /**
   * Locate user role.
   * 确定用户组
   * @return 1:root
   *         2:second
   *         3:leader
   *         4:member
   */
  uint8_t locateUserRole(uint16_t pageID);

  /**
   * Locate user range by group.
   * 根据用户组确定指纹区间
   */
  uint16_t locateUserRangeMax(uint8_t groupID);
  uint16_t locateUserRangeMin(uint8_t groupID);

  /**
   * Read latest fingerprint location from EEPROM.
   * 从EEPROM中读取最新指纹位置
   */
  uint16_t readFromEEPROM(uint8_t groupID);

  /**
   * Save latest fingerprint location to EEPROM.
   * 在EEPROM中保存最新指纹位置
   */
  void saveToEEPROM(uint8_t groupID, uint16_t location);

public:
  R308Linker();

  /**
   * Read from sensor and search fingerprint among library.
   * 读取手指并搜索指纹库
   */
  bool readAndSearch();
  uint16_t readAndSearch(uint8_t bufferID, uint16_t startPageID,
                         uint16_t pageNum);

  /**
   * Scan and save fingerprint to the corresponding group.
   * 扫描并保存指纹到对应组
   */
  bool readAndSave(uint8_t groupID);
};

#endif
