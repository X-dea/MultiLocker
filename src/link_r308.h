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

class R308Linker {
private:
  void saveFingerId(unsigned short pageID);

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
   * Locate user role.
   * 确定用户组
   * @return 1:root
   *         2:second
   *         3:leader
   *         4:member
   */
  uint8_t locateUserRole(uint16_t pageID);
};

#endif
