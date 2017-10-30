/*!
   \file CTB_R308.cpp
   \brief CTBeta R308 Library (GPLv3) Support by CTBeta Team http://ctbeta.org/
   \author Jason C.H
   \date Nov. 2016

   A library for R308 fingerprint module.\n
   一个R308指纹模块库。
*/

#include <CTB_R308.h>

CTB_R308::CTB_R308() {}

/*!
   \brief Initialize module
   \brief 初始化函数库，对指纹模块进行握手验证
   \return true (Finished.完成)
*/
bool CTB_R308::init() {
  Serial.begin(57600);
  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packInit[0], 10);
  delay(10);
  return true;
}

/*!
   \brief Get fingerprint image.
   \brief 获得指纹图像
   \return -1:Failed.失败
            0:Succeeded.成功
            1:Pack error.收包有误
            2:No finger.传感器无手指
            3:Scan Failed.录入失败
*/
short CTB_R308::cmdGetImg() {
  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packGetImg[0], 6);
  delay(300);
  if (serialRead() == true)
    return packSerialRead[2];
  else
    return -1;
}

/*!
   \brief Put fingerprint image to buffer1
   \brief 将图像转换成特征码存放在Buffer1中
   \return
*/
short CTB_R308::cmdToBuffer1() {
  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packToBuffer1[0], 7);
  delay(500);
  if (serialRead() == true)
    return packSerialRead[2];
  else
    return -1;
}

/*!
   \brief Put fingerprint image to buffer2
   \brief 将图像转换成特征码存放在Buffer2中
   \return
*/
short CTB_R308::cmdToBuffer2() {
  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packToBuffer2[0], 7);
  delay(500);
  if (serialRead() == true)
    return packSerialRead[2];
  else
    return -1;
}

/*!
   \brief Merge buffers and generate model.
   \brief 将BUFFER1 跟 BUFFER2 中的特征码合并成指纹模版
   \return
*/
bool CTB_R308::cmdRegModel() {
  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packRegModel[0], 6);
  delay(50);
  return serialRead();
}

/*!
   \brief Delete all models.
   \brief 删除指纹模块里的所有指纹模版
   \return
*/
bool CTB_R308::cmdEmpty() {
  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packEmpty[0], 6);
  delay(1000);
  return serialRead();
}

/**
* 函 数 名：cmdSaveFinger
* 功能描述：将BUFFER1中的特征码存放到指定的位置
* 输入参数：指纹ID
* 返 回 值：true/false
*/
bool CTB_R308::cmdSaveFinger(unsigned int ID_temp) {
  volatile unsigned int Sum_temp = 0;

  packSaveFinger[5] = (ID_temp & 0xFF00) >> 8;
  packSaveFinger[6] = (ID_temp & 0x00FF);

  for (int i = 0; i < 7; i++)
    Sum_temp = Sum_temp + packSaveFinger[i];

  packSaveFinger[7] = (Sum_temp & 0xFF00) >> 8;
  packSaveFinger[8] = Sum_temp & 0x00FF;

  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packSaveFinger[0], 9);
  delay(100);
  return serialRead();
}

/**
* 函 数 名：cmdSearch
* 功能描述：搜索全部用户
* 输入参数：无
* 返 回 值：无
*/
bool CTB_R308::cmdSearch() {
  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packSearch[0], 11);
  delay(100);
  return serialRead();
}

/**
* 函 数 名：cmdDeleteModel
* 功能描述：删除指纹模块里的指定指纹模版
* 输入参数：指纹ID
* 返 回 值：true/false
*/
bool CTB_R308::cmdDeleteModel(unsigned int ID_temp) {
  volatile unsigned int Sum_temp = 0;

  packDeleteModel[4] = (ID_temp & 0xFF00) >> 8;
  packDeleteModel[5] = (ID_temp & 0x00FF);

  for (int i = 0; i < 8; i++)
    Sum_temp = Sum_temp + packDeleteModel[i];

  packDeleteModel[8] = (Sum_temp & 0xFF00) >> 8;
  packDeleteModel[9] = Sum_temp & 0x00FF;

  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packDeleteModel[0], 10);
  delay(100);
  return serialRead();
}

/*!
   \brief Clean serial port cache.
   \brief 清空串口缓存
*/
void CTB_R308::serialClean() {
  for (int i = 0; i < 10; i++) {
    packSerialRead[i] = 0xFF;
  }
  while (Serial.read() >= 0) {
  }
}

/*!
   \brief Read data from serial port.
   \brief 从串口读取数据
   \return TRUE/FALSE (Finished完成/Failed失败)
*/
bool CTB_R308::serialRead() {

  // Wait for data stream.等待数据流
  long timeStart = millis();
  while (Serial.available() <= 0 && millis() - timeStart >= 0 &&
         millis() - timeStart < 3000) {
  }

  // Verify pack head & sign.校验包头与标识
  if (Serial.read() == 0xEF && Serial.read() == 0x01) {
    for (int i = 0; i < 4; i++) {
      if (Serial.read() != packHead[i + 2])
        return false;
    }
    if (Serial.read() != 0x07)
      return false;
  } else
    return false;

  // Receive pack.接收包
  packSerialRead[0] = ((Serial.read() << 8) | Serial.read());
  for (int i = 1; i <= packSerialRead[0]; i++)
    packSerialRead[i] = Serial.read();
  return true;
}
