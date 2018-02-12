/*!
   \file link_r308.cpp
   \brief Linker for R308 Module
   \author Jason C.H
   \date Feb. 2018
*/

#include "config.h"
#include "link_r308.h"
#include <X_R308.h>

R308 r308;

LR308::LR308(){};

/*!
   \brief Search fingerprint among library.
   \brief 读取手指并搜索指纹库
   \return 成功返回ture 失败返回false
*/
bool LR308::searchFinger() {
  r308.cmdGetImg();
  r308.cmdToBuffer1();
  r308.cmdSearch(1, 1, 500);
  if (r308.packSerialRead[1] == 0x0)
    return true;
  else
    return false;
}
