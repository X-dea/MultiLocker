/**
 * @brief User of system
 *
 * @file user.hpp
 * @author Jason C.H
 * @date 2018-09-01
 */

#ifndef USER_H
#define USER_H

#include <Arduino.h>
#include "config.h"

enum UserRole { kAllRole, kRootRole, kSecondRole, kThirdRole, kFourthRole };

class User {
 public:
  String name;
  uint16_t id;
  UserRole role;
  String registerDate;

  User(String name, uint16_t id, UserRole role)
      : name(name), id(id), role(role) {}

#ifdef ENABLE_DEBUG_MODE
  /**
   * @brief Provide function to print user information to serial port
   * @brief 提供将当前用户信息输出到串口的方法
   */
  void printToSerial() {
    Serial.println("\n---UserInfo---");
    Serial.print("Name:");
    Serial.println(name);
    Serial.print("ID:");
    Serial.println(id);
    Serial.print("Role:");
    Serial.println(role);
    Serial.print("Register date:");
    Serial.println(registerDate);
  }
#endif
};

#endif