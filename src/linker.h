/**
 * @brief A common abstruct class for linking to authentication modules.
 * All the linkers should inherit from this common Linker class and implement
 * 所有的模块连接器应当继承 Linker 类并实现方法
 *
 * @file linker.h
 * @author Jason C.H
 * @date 2018-09-01
 */

#ifndef LINKER_H
#define LINKER_H

#include <Arduino.h>
#include "user.hpp"

class Linker {
 public:
  /**
   * @brief Init module.
   * @brief 初始化模块
   */
  virtual void Init() = 0;

  /**
   * @brief Get user from module and return
   * @brief 从模块获取用户并返回
   *
   * @return User The user got from modules
   */
  virtual User GetUser() = 0;

  /**
   * @brief Auth user with given role.
   * @brief 用户认证
   *
   * @param user The user under match.等待比对的用户
   * @param role The role to match.等待比对的用户组
   * @return true Role match succeed.比对成功
   * @return false Role match failed.比对失败
   */
  virtual bool Auth(User user, const UserRole &role) = 0;

  /**
   * @brief Module setup mode
   * @brief 模块配置模式
   */
  virtual void SetupMode() = 0;

  /**
   * @brief Register new user to given role
   * @brief 注册新用户到给定用户组
   *
   * @param role User role.用户组
   * @return true Register succeed.注册成功
   * @return false Register failed.注册失败
   */
  virtual bool RegisterUser(UserRole role) = 0;

  /**
   * @brief Delete user
   * @brief 移除用户
   *
   * @param *user User to delete.待删除的用户
   * @return true Delete succeed.移除成功
   * @return false Delete failed.移除失败
   */
  virtual bool DeleteUser(User &user) = 0;
};

#endif