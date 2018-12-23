/**
 * @brief Linker for R308 module
 *
 * @file linker_r308.cpp
 * @author Jason C.H
 * @date 2018-09-01
 */
#include "linker_r308.h"

R308 r308;  // Single object of R308 library

/**
 * @brief Read latest fingerprint location from EEPROM.
 * @brief 从 EEPROM 中读取最新指纹位置
 *
 * @param role User role.用户组
 * @return uint16_t Location.指纹位置
 */
uint16_t R308Linker::readFromEEPROM(UserRole role) {
  uint16_t fingerprintPointer = kFingerprintPointerStart + 2 * (role - 1);
  return (EEPROM.read(fingerprintPointer) << 8) |
         EEPROM.read(fingerprintPointer + 1);
}

/**
 * @brief Save latest fingerprint location to EEPROM.
 * @brief 在 EEPROM 中保存最新指纹位置
 *
 * @param role User role.用户组
 * @param location Location of latest fingerprint.最新指纹位置
 */
void R308Linker::saveToEEPROM(UserRole role, uint16_t location) {
  uint16_t fingerprintPointer = kFingerprintPointerStart + 2 * (role - 1);
  EEPROM.update(fingerprintPointer, location >> 8);
  EEPROM.update(fingerprintPointer + 1, location & 0x00FF);
}

/**
 * @brief Locate user role by fingerprint page ID
 * @brief 根据指纹存储位置确定用户组
 *
 * @param pageID Fingerprint page ID.指纹库位置
 * @return UserRole User role.用户组
 */
UserRole R308Linker::getUserRole(uint16_t pageID) {
  if (pageID >= kRoleRootMin && pageID <= kRoleRootMax)
    return kRootRole;
  else if (pageID >= kRoleSecondMin && pageID <= kRoleSecondMax)
    return kSecondRole;
  else if (pageID >= kRoleThirdMin && pageID <= kRoleThirdMax)
    return kThirdRole;
  else if (pageID >= kRoleFourthMin && pageID <= kRoleFourthMax)
    return kFourthRole;
  else
    return kAllRole;
}

/**
 * @brief Locate user role range max
 * @brief 根据用户组确定指纹库区间上限
 *
 * @param role User role.用户组
 * @return uint16_t Page location.指纹库位置
 */
uint16_t R308Linker::getRoleLocationRangeMax(UserRole role) {
  switch (role) {
    case kRootRole:
      return kRoleRootMax;
    case kSecondRole:
      return kRoleSecondMax;
    case kThirdRole:
      return kRoleThirdMax;
    default:
      return kRoleFourthMax;
  }
}

/**
 * @brief Locate user role range min
 * @brief 根据用户组确定指纹库区间下限
 *
 * @param role role User role.用户组
 * @return uint16_t Page location.指纹库位置
 */
uint16_t R308Linker::getRoleLocationRangeMin(UserRole role) {
  switch (role) {
    case kFourthRole:
      return kRoleFourthMin;
    case kThirdRole:
      return kRoleThirdMin;
    case kSecondRole:
      return kRoleSecondMin;
    default:
      return kRoleRootMin;
  }
}

R308Linker::R308Linker() {}
R308Linker::~R308Linker() {}

/**
 * @brief Get user from modules and return
 * @brief 从模块获取用户并返回
 *
 * @return User The user got from modules
 */
User R308Linker::getUser() {
  int8_t status = 0;
  status += abs(r308.cmdGetImg());
  status += abs(r308.cmdToBuffer1());
  status += abs(r308.cmdSearch(1, 1, 500));
  if (status != 0) {
    User user("Error", 0, kAllRole);
    return user;
  }
  uint16_t id = r308.packSerialRead[1] << 8 | r308.packSerialRead[2];
  UserRole role = getUserRole(id);
  User user("FPUser", id, role);
  return user;
}

/**
 * @brief Get user from modules and check role
 * @brief 从模块中获取用户并认证
 *
 * @param role The role to match.等待比对的用户组
 * @return true Role match succeed.比对成功
 * @return false Role match failed.比对失败
 */
bool R308Linker::auth(UserRole role) {
  User user = getUser();
  if (user.name == "Error") return false;
  if (user.role == role || role == kAllRole) return true;
}

/**
 * @brief Module setup mode
 * @brief 模块配置模式
 */
void R308Linker::setupMode() {
  while (digitalRead(PIN_DETECT) != LOW) {
  }
  delay(300);
  r308.init();
  User user = getUser();
  if (user.role == kAllRole || user.role == kRoleFourthMax) return;
  while (digitalRead(PIN_DETECT) != LOW) {
  }
  registerUser((UserRole)(user.role + 1));
}

/**
 * @brief Register new user to given role
 * @brief 注册新用户到给定用户组
 *
 * @param role User role.用户组
 * @return true Register succeed.注册成功
 * @return false Register failed.注册失败
 */
bool R308Linker::registerUser(UserRole role) {
  int8_t status = 0;
  status += abs(r308.cmdGetImg());
  status += abs(r308.cmdToBuffer1());
  status += abs(r308.cmdGetImg());
  status += abs(r308.cmdToBuffer2());
  status += abs(r308.cmdRegModel());
  if (status != 0) return false;
  uint16_t offset = readFromEEPROM(role) + 1;
  if (offset > getRoleLocationRangeMax(role)) return false;
  r308.cmdSaveFinger(1, offset);
  saveToEEPROM(role, offset);
  return true;
}

/**
 * @brief Delete user
 * @brief 移除用户
 *
 * @param *user User to delete.待删除的用户
 * @return true Delete succeed.移除成功
 * @return false Delete failed.移除失败
 */
bool R308Linker::deleteUser(User *user) {
  r308.cmdDeleteModel(user->id, 1);
  return true;
}
