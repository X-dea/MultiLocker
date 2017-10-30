/**
* MultiLocker (GPLv3)
* Support by CTBeta Team http://ctbeta.org/
* Created by Jason C.H Feb. 2017
*/

#include "config.h"
#include "link_r308.h"
#include <CTB_R308.h>

R308 r308;

LR308::LR308() { Serial.begin(57600); };

/**
* 函 数 名：setupMode
* 功能描述：设定模式
* 输入参数：无
* 返 回 值：无
*/
void LR308::setupMode() {}

/**
* 函 数 名：searchFinger
* 功能描述：读取手指并搜索指纹库
* 输入参数：无
* 返 回 值：找到返回ture 未找到返回false
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
