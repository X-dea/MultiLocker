/*!
   \file link_r308.cpp
   \brief Linker for R308 Module
   \author Jason C.H
   \date Feb. 2018
*/

#include "link_r308.h"
#include "config.h"
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