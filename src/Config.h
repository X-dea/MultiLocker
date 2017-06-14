/**
* MultiLocker (GPLv3)
* Support by CTBeta Team
* Created by Jason C.H Feb 2017
*/
#ifndef CONFIG_H
#define CONFIG_H

//HAL DEFINITION
//定义硬件层
#include "HAL_ArduProMini.h"

//AUTHTYPE DEFINITION(ONLY ONE)
//定义启用的认证类型(唯一启用)
#define USE_RC522
//#define USE_LB522
//#define USE_FINGERPRINT

//DATALINK DEFINETION(ONLY ONE)
//定义启用的认证存储（唯一启用）
#define USE_LOCAL

//MYSQL DEFINITION
//启用MYSQL数据库(仅在网络存储启用时可定义)
//#define USE_MYSQL
#ifdef  USE_MYSQL
  #define MYSQL_ADDRESS MYADDRESS
  #define MYSQL_DATABASE MultiLockers
  #define MYSQL_PASSWOED MYPASSWORFD
  #define MYSQL_TABLE MultiLockers
#endif


#endif
