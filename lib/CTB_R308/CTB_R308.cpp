/*!
   \file CTB_R308.cpp
   \brief CTBeta R308 Library (GPLv3) Support by CTBeta Team http://ctbeta.org/
   \author Jason C.H
   \date Nov. 2016

   A library for R308 fingerprint module.\n
   一个R308指纹模块库。
*/

#include <CTB_R308.h>

unsigned char R308::packHead[6] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF};
unsigned char R308::packInit[10] = {0x01, 0x00, 0x07, 0x13, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x1B};
unsigned char R308::packGetImg[6] = {0x01, 0x00, 0x03, 0x01, 0x0, 0x05};
unsigned char R308::packToBuffer1[7] = {0x01, 0x0, 0x04, 0x02, 0x01, 0x0, 0x08};
unsigned char R308::packToBuffer2[7] = {0x01, 0x0, 0x04, 0x02, 0x02, 0x0, 0x09};
unsigned char R308::packRegModel[6] = {0x01, 0x0, 0x03, 0x05, 0x0, 0x09};
unsigned char R308::packEmpty[6] = {0x01, 0x0, 0x03, 0x0d, 0x00, 0x11};

R308::R308() {}

/*!
   \brief Initialize module
   \brief 初始化函数库，对指纹模块进行握手验证
   \return true:Finished.完成
*/
bool R308::init() {
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
   \return -1:Failed.收包失败
            0:Succeeded.成功
            1:Pack error.收包有误
            2:No finger.传感器无手指
            3:Scan Failed.录入失败
*/
short R308::cmdGetImg() {
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
   \brief 将图像转换成特征码存放在缓冲区1中
   \return -1:Failed.收包失败
            0:Succeeded.成功
            1:Pack error.收包有误
            6:Bad image.图像太乱
            7:Few features.特征点过少
            15:No image in buffer.没有图像
*/
short R308::cmdToBuffer1() {
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
   \brief 将图像转换成特征码存放在缓冲区2中
   \return -1:Failed.收包失败
            0:Succeeded.成功
            1:Pack error.收包有误
            6:Bad image.图像太乱
            7:Few features.特征点过少
            15:No image in buffer.没有图像
*/
short R308::cmdToBuffer2() {
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
   \brief 将缓冲区中的特征码合并成指纹模版
   \return -1:Failed.收包失败
            0:Succeeded.成功
            1:Pack error.收包有误
            A:Merge error:Not same finger.合并错误:非同一手指
*/
short R308::cmdRegModel() {
  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packRegModel[0], 6);
  delay(50);
  if (serialRead() == true)
    return packSerialRead[2];
  else
    return -1;
}

/*!
   \brief Delete all models.
   \brief 删除指纹模块里的所有指纹模版
   \return -1:Failed.收包失败
            0:Succeeded.成功
            1:Pack error.收包有误
            11:Empty failed.清空失败
*/
short R308::cmdEmpty() {
  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packEmpty[0], 6);
  delay(1000);
  if (serialRead() == true)
    return packSerialRead[2];
  else
    return -1;
}

/*!
   \brief Save fingerprint from buffer to page.
   \brief 将缓冲区中的特征码存放到指定的位置
   \param bufferID(缓冲区号),pageID(指纹库位置)
   \return -1:Failed.收包失败
            0:Succeeded.成功
            1:Pack error.收包有误
            B:PageID out of range.超出指纹库范围
            18:Flash error.写Flash出错
*/
short R308::cmdSaveFinger(unsigned short bufferID, unsigned short pageID) {
  volatile unsigned int Sum = 0;

  packSaveFinger[4] = bufferID;
  packSaveFinger[5] = (pageID & 0xFF00) >> 8;
  packSaveFinger[6] = pageID & 0x00FF;

  for (short i = 0; i < 7; i++)
    Sum += packSaveFinger[i];

  packSaveFinger[7] = (Sum & 0xFF00) >> 8;
  packSaveFinger[8] = Sum & 0x00FF;

  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packSaveFinger[0], 9);
  delay(100);
  if (serialRead() == true)
    return packSerialRead[2];
  else
    return -1;
}

/*!
   \brief Search fingerprint among pages.
   \brief 从指纹库中搜索指纹
   \param bufferID(缓冲区号),startPageID(指纹库起始页),pageNum(页数)
   \return -1:Failed.收包失败
            0:Finished.搜索完成
            1:Pack error.收包有误
            9:Nothing matched.未搜索到
*/
short R308::cmdSearch(unsigned short bufferID, unsigned short startPageID,
                      unsigned short pageNum) {
  volatile unsigned int Sum = 0;

  packSearch[4] = bufferID;
  packSearch[5] = (startPageID & 0xFF00) >> 8;
  packSearch[6] = (startPageID & 0x00FF);
  packSearch[7] = (pageNum & 0xFF00) >> 8;
  packSearch[8] = pageNum & 0x00FF;

  for (short i = 0; i < 9; i++)
    Sum += packSearch[i];

  packSearch[9] = (Sum & 0xFF00) >> 8;
  packSearch[10] = Sum & 0x00FF;

  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packSearch[0], 11);
  delay(100);
  if (serialRead() == true)
    return packSerialRead[2];
  else
    return -1;
}

/*!
   \brief Delete models.
   \brief 删除指纹模块里的指定指纹模版
   \param startPageID(指纹库起始页),pageNum(页数)
   \return -1:Failed.收包失败
            0:Succeeded.成功
            1:Pack error.收包有误
            10:Delete failed.删除失败
*/
short R308::cmdDeleteModel(unsigned short startPageID, unsigned short pageNum) {
  volatile unsigned int Sum = 0;

  packDeleteModel[4] = (startPageID & 0xFF00) >> 8;
  packDeleteModel[5] = startPageID & 0x00FF;
  packDeleteModel[6] = (pageNum & 0xFF00) >> 8;
  packDeleteModel[7] = pageNum & 0x00FF;

  for (short i = 0; i < 8; i++)
    Sum += packDeleteModel[i];

  packDeleteModel[8] = (Sum & 0xFF00) >> 8;
  packDeleteModel[9] = Sum & 0x00FF;

  serialClean();
  Serial.write(&packHead[0], 6);
  Serial.write(&packDeleteModel[0], 10);
  delay(100);
  if (serialRead() == true)
    return packSerialRead[2];
  else
    return -1;
}

/*!
   \brief Clean serial port cache.
   \brief 清空串口缓存
*/
void R308::serialClean() {
  for (short i = 0; i < 10; i++) {
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
bool R308::serialRead() {

  // Wait for data stream.等待数据流
  long timeStart = millis();
  while (Serial.available() <= 0 && millis() - timeStart >= 0 &&
         millis() - timeStart < 3000) {
  }

  // Verify pack head & sign.校验包头与标识
  if (Serial.read() == 0xEF && Serial.read() == 0x01) {
    for (short i = 0; i < 4; i++) {
      if (Serial.read() != packHead[i + 2])
        return false;
    }
    if (Serial.read() != 0x07)
      return false;
  } else
    return false;

  // Receive pack.接收包
  packSerialRead[0] = ((Serial.read() << 8) | Serial.read());
  for (short i = 1; i <= packSerialRead[0]; i++)
    packSerialRead[i] = Serial.read();
  return true;
}
