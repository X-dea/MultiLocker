/*!
   \file link_r308.cpp
   \brief Linker for R308 Module
   \author Jason C.H
   \date Feb. 2018
*/

#include "link_r308.h"
#include "config.h"
#include <EEPROM.h>
#include <x_r308.h>

R308 r308;

R308Linker::R308Linker(){};

/**
 * Read from sensor and search fingerprint among library.
 * 读取手指并搜索指纹库
 */
bool R308Linker::readAndSearch() {
  r308.cmdGetImg();
  r308.cmdToBuffer1();
  r308.cmdSearch(1, 1, 500);
  return (r308.packSerialRead[1] == 0x0) ? true : false;
}
uint16_t R308Linker::readAndSearch(uint8_t bufferID, uint16_t startPageID,
                                   uint16_t pageNum) {
  r308.cmdGetImg();
  r308.cmdToBuffer1();
  r308.cmdSearch(bufferID, startPageID, pageNum);
  if (r308.packSerialRead[1] != 0x0)
    return -1;
  return (r308.packSerialRead[2] << 8) | r308.packSerialRead[3];
}

/**
 * Scan and save fingerprint to the corresponding group.
 * 扫描并保存指纹到对应组
 */
bool R308Linker::readAndSave(uint8_t groupID) {
  r308.cmdGetImg();
  r308.cmdToBuffer1();
  r308.cmdGetImg();
  r308.cmdToBuffer2();
  r308.cmdRegModel();
  auto offset = readFromEEPROM(groupID) + 1;
  if (offset > kRoleMemberMax)
    return false;
  r308.cmdSaveFinger(1, offset);
  saveToEEPROM(groupID, offset);
  return true;
}

/**
 * Locate user role.
 * 确定用户组
 * @return 1:root
 *         2:second
 *         3:leader
 *         4:member
 *         -1: none
 */
uint8_t R308Linker::locateUserRole(uint16_t pageID) {
  if (pageID >= kRoleMemberMin && pageID <= kRoleMemberMax)
    return 4;
  if (pageID >= kRoleLeaderMin && pageID <= kRoleLeaderMax)
    return 3;
  if (pageID >= kRoleSecondMin && pageID <= kRoleSecondMax)
    return 2;
  if (pageID >= kRoleRootMin && pageID <= kRoleRootMax)
    return 1;
  return -1;
}

/**
 * Locate user range by group.
 * 根据用户组确定指纹区间
 */
uint16_t R308Linker::locateUserRangeMax(uint8_t groupID) {
  switch (groupID) {
  case 1:
    return kRoleRootMax;
  case 2:
    return kRoleSecondMax;
  case 3:
    return kRoleLeaderMax;
  default:
    return kRoleMemberMax;
  }
}
uint16_t R308Linker::locateUserRangeMin(uint8_t groupID) {
  switch (groupID) {
  case 4:
    return kRoleMemberMin;
  case 3:
    return kRoleLeaderMin;
  case 2:
    return kRoleSecondMin;
  default:
    return kRoleRootMin;
  }
}

/**
 * Read latest fingerprint location from EEPROM.
 * 从EEPROM中读取最新指纹位置
 */
uint16_t readFromEEPROM(uint8_t groupID) {
  uint16_t fingerprintPointer = kFingerprintPointerStart + 2 * (groupID - 1);
  return (EEPROM.read(fingerprintPointer) << 8) |
         EEPROM.read(fingerprintPointer + 1);
}

/**
 * Save latest fingerprint location to EEPROM.
 * 在EEPROM中保存最新指纹位置
 */
void saveToEEPROM(uint8_t groupID, uint16_t location) {
  uint16_t fingerprintPointer = kFingerprintPointerStart + 2 * (groupID - 1);
  EEPROM.write(fingerprintPointer, location >> 8);
  EEPROM.write(fingerprintPointer + 1, location & 0x00FF);
}