/**
* CTBeta R308 Library (GPLv3)
* Support by CTBeta Team http://ctbeta.org/
* Created by Jason C.H Nov 2016
*/

#include <Arduino.h>
#include <CTB_R308.h>

CTB_R308::CTB_R308() {}

/**
* 函 数 名：init
* 功能描述：初始化函数库，对指纹模块进行握手验证
* 输入参数：无
* 返 回 值：无
*/
bool CTB_R308::init() {
  Serial.begin(57600);
  SerialClean();
  Serial.write(&FP_Pack_Head[0], 6);
  Serial.write(&FP_Init[0], 10);
  delay(10);
  return true;
}
/**
* 函 数 名：Cmd_Get_Img
* 功能描述：获得指纹图像
* 输入参数：无
* 返 回 值：无
*/
bool CTB_R308::Cmd_Get_Img() {
  SerialClean();
  Serial.write(&FP_Pack_Head[0], 6);
  Serial.write(&FP_Get_Img[0], 6);
  delay(300);
  return SerialRead();
}

/**
* 函 数 名：Cmd_Img_To_Buffer1
* 功能描述：将图像转换成特征码存放在Buffer1中
* 输入参数：无
* 返 回 值：无
*/
bool CTB_R308::Cmd_Img_To_Buffer1() {
  SerialClean();
  Serial.write(&FP_Pack_Head[0], 6);
  Serial.write(&FP_Img_To_Buffer1[0], 7);
  delay(500);
  return SerialRead();
}

/**
* 函 数 名：Cmd_Img_To_Buffer2
* 功能描述：将图像转换成特征码存放在Buffer2中
* 输入参数：无
* 返 回 值：无
*/
bool CTB_R308::Cmd_Img_To_Buffer2() {
  SerialClean();
  Serial.write(&FP_Pack_Head[0], 6);
  Serial.write(&FP_Img_To_Buffer2[0], 7);
  delay(500);
  return SerialRead();
}

/**
* 函 数 名：Cmd_Reg_Model
* 功能描述：将BUFFER1 跟 BUFFER2 中的特征码合并成指纹模版
* 输入参数：无
* 返 回 值：无
*/
bool CTB_R308::Cmd_Reg_Model() {
  SerialClean();
  Serial.write(&FP_Pack_Head[0], 6);
  Serial.write(&FP_Reg_Model[0], 6);
  delay(50);
  return SerialRead();
}

/**
* 函 数 名：Cmd_Save_Finger
* 功能描述：将BUFFER1中的特征码存放到指定的位置
* 输入参数：指纹ID
* 返 回 值：true/false
*/
bool CTB_R308::Cmd_Save_Finger(unsigned int ID_temp) {
  volatile unsigned int Sum_temp = 0;

  FP_Save_Finger[5] = (ID_temp & 0xFF00) >> 8;
  FP_Save_Finger[6] = (ID_temp & 0x00FF);

  for (int i = 0; i < 7; i++)
    Sum_temp = Sum_temp + FP_Save_Finger[i];

  FP_Save_Finger[7] = (Sum_temp & 0xFF00) >> 8;
  FP_Save_Finger[8] = Sum_temp & 0x00FF;

  SerialClean();
  Serial.write(&FP_Pack_Head[0], 6);
  Serial.write(&FP_Save_Finger[0], 9);
  delay(100);
  return SerialRead();
}

/**
* 函 数 名：Cmd_Delete_All_Model
* 功能描述：删除指纹模块里的所有指纹模版
* 输入参数：无
* 返 回 值：true/false
*/
bool CTB_R308::Cmd_Delete_All_Model() {
  SerialClean();
  Serial.write(&FP_Pack_Head[0], 6);
  Serial.write(&FP_Delet_All_Model[0], 6);
  delay(1000);
  return SerialRead();
}

/**
* 函 数 名：Cmd_Delete_Model
* 功能描述：删除指纹模块里的指定指纹模版
* 输入参数：指纹ID
* 返 回 值：true/false
*/
bool CTB_R308::Cmd_Delete_Model(unsigned int ID_temp) {
  volatile unsigned int Sum_temp = 0;

  FP_Delete_Model[4] = (ID_temp & 0xFF00) >> 8;
  FP_Delete_Model[5] = (ID_temp & 0x00FF);

  for (int i = 0; i < 8; i++)
    Sum_temp = Sum_temp + FP_Delete_Model[i];

  FP_Delete_Model[8] = (Sum_temp & 0xFF00) >> 8;
  FP_Delete_Model[9] = Sum_temp & 0x00FF;

  SerialClean();
  Serial.write(&FP_Pack_Head[0], 6);
  Serial.write(&FP_Delete_Model[0], 10);
  delay(100);
  return SerialRead();
}

/**
* 函 数 名：Cmd_Search_Finger
* 功能描述：搜索全部用户
* 输入参数：无
* 返 回 值：无
*/
bool CTB_R308::Cmd_Search_Finger() {
  SerialClean();
  Serial.write(&FP_Pack_Head[0], 6);
  Serial.write(&FP_Search[0], 11);
  delay(1000);
  return SerialRead();
}

/**
* 函 数 名：SerialClean
* 功能描述：清空串口缓存
* 输入参数：无
* 返 回 值：无
*/
void CTB_R308::SerialClean() {
  for (int i = 0; i < 10; i++) {
    FP_SerialRead[i] = 0;
  }
  while (Serial.read() >= 0) {
  }
}

/**
* 函 数 名：SerialRead
* 功能描述：进行串口返回读取
* 输入参数：无
* 返 回 值：成功true/不成功false
*/
bool CTB_R308::SerialRead() {
  //等待应答
  while (Serial.available() <= 0) {
  }
  //验证模块地址和应答包
  if (Serial.read() == 0xEF && Serial.read() == 0x01) {
    for (int i = 0; i < 4; i++) {
      if (Serial.read() != FP_Pack_Head[i + 2])
        return false;
    }
    if (Serial.read() != 0x07)
      return false;
  } else
    return false;
  //接收包
  Serial.read(); //去除空字节
  FP_SerialRead[0] = Serial.read();
  for (int i = 1; i <= FP_SerialRead[0]; i++)
    FP_SerialRead[i] = Serial.read();
  return true;
}
