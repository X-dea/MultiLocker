/**
* MultiLocker (GPLv3)
* Support by CTBeta Team http://ctbeta.org/
* Created by Jason C.H Feb 2017
*/

#include "Config.h"
#include "Link_r308.h"
#include <CTB_R308.h>

CTB_R308 r308;

R308::R308() { Serial.begin(57600); };

/**
* 函 数 名：setupMode
* 功能描述：设定模式
* 输入参数：无
* 返 回 值：无
*/
void R308::setupMode() {
  
}

/**
* 函 数 名：searchFinger
* 功能描述：读取手指并搜索指纹库
* 输入参数：无
* 返 回 值：找到返回ture 未找到返回false
*/
bool R308::searchFinger() {
  r308.Cmd_Get_Img();
  r308.Cmd_Img_To_Buffer1();
  r308.Cmd_Search_Finger();
  if (r308.FP_SerialRead[1] == 0x0)
    return true;
  else
    return false;
}

/**
* 函 数 名：saveFingerId
* 功能描述：保存指纹
* 输入参数：指纹库ID
* 返 回 值：无
*/
void R308::saveFingerId(int ID_temp) {
  Serial.println("Saving!");
  Serial.println(r308.Cmd_Get_Img());
  Serial.println(r308.Cmd_Img_To_Buffer1());
  Serial.println(r308.Cmd_Get_Img());
  Serial.println(r308.Cmd_Img_To_Buffer2());
  Serial.println(r308.Cmd_Reg_Model());
  Serial.println(r308.Cmd_Save_Finger(ID_temp));
}
