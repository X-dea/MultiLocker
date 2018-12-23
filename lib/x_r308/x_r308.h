/**
 * @brief A library for R308 fingerprint module.
 *
 * @file x_r308.h
 * @author Jason C.H
 * @date 2018-09-02
 */

#ifndef R308_H
#define R308_H

#include <Arduino.h>
#include <avr/pgmspace.h>

/**
 * Use Hardware Serial 0
 * 使用硬件串口 0
 */
#define SerPort Serial

class R308 {
 private:
  static const uint8_t packHead[6];
  static const uint8_t packInit[10];
  static const uint8_t packGetImg[6];
  static const uint8_t packToBuffer1[7];
  static const uint8_t packToBuffer2[7];
  static const uint8_t packRegModel[6];
  static const uint8_t packEmpty[6];

  /*!
    Save fingerprint from buffer to page.从指定缓冲区保存指纹
    sign  | length | command | bufferID | pageID | sum
    1byte | 2byte  | 1byte   | 1byte    | 2byte  | 2byte
  */
  uint8_t packSaveFinger[9] = {0x01, 0x00, 0x06, 0x06, 0x01,
                               0x00, 0x02, 0x0,  0x0};
  /*!
    Search fingerprint among pages.从指纹库中搜索
    sign  | length | command | bufferID | start | num   | sum
    1byte | 2byte  | 1byte   | 1byte    | 2byte | 2byte | 2byte
  */
  uint8_t packSearch[11] = {0x01, 0x0,  0x08, 0x04, 0x01, 0x0,
                            0x0,  0x01, 0xF4, 0x01, 0x03};

  /*!
    Delete N fingerprints from a pageID.从指定pageID删除N个指纹
    sign  | length | command | pageID | N     | sum
    1byte | 2byte  | 1byte   | 2byte  | 2byte | 2byte
  */
  uint8_t packDeleteModel[10] = {0x01, 0x00, 0x07, 0x0C, 0x0,
                                 0x0,  0x0,  0x1,  0x0,  0x0};

  /**
   * @brief Send package (PGM)
   * @brief 发送包 (PGM)
   *
   * @param pack Package to send.需要发送的包
   * @param length 包长度
   */
  void sendPack(const uint8_t *pack, uint8_t length);

  /**
   * @brief Clean serial port cache.
   * @brief 清空串口缓存
   */
  void serialClean();

  /**
   * @brief Read data from serial port.
   * @brief 从串口读取数据
   *
   * @return true Finished.收包完成
   * @return false Failed.收包或包头校验失败
   */
  bool serialRead();

 public:
  uint8_t packSerialRead[10];  // Origin retuens.读取的返回数据

  R308();

  /**
   * @brief Initialize module
   * @brief 初始化函数库，对指纹模块进行握手验证
   */
  void init();

  /**
   * @brief Get fingerprint image.
   * @brief 获得指纹图像
   *
   * @return int8_t -1:Failed.收包失败
   *                 0:Succeeded.成功
   *                 1:Pack error.收包有误
   *                 2:No finger.传感器无手指
   *                 3:Scan Failed.录入失败
   */
  int8_t cmdGetImg();

  /**
   * @brief Put fingerprint image to buffer1
   * @brief 将图像转换成特征码存放在缓冲区 1 中
   *
   * @return int8_t -1:Failed.收包失败
   *                 0:Succeeded.成功
   *                 1:Pack error.收包有误
   *                 6:Bad image.图像太乱
   *                 7:Few features.特征点过少
   *                 15:No image in buffer.没有图像
   */
  int8_t cmdToBuffer1();

  /**
   * @brief Put fingerprint image to buffer2
   * @brief 将图像转换成特征码存放在缓冲区 2 中
   *
   * @return int8_t -1:Failed.收包失败
   *                 0:Succeeded.成功
   *                 1:Pack error.收包有误
   *                 6:Bad image.图像太乱
   *                 7:Few features.特征点过少
   *                 15:No image in buffer.没有图像
   */
  int8_t cmdToBuffer2();

  /**
   * @brief Merge buffers and generate model.
   * @brief 将缓冲区中的特征码合并成指纹模版
   *
   * @return int8_t -1:Failed.收包失败
   *                 0:Succeeded.成功
   *                 1:Pack error.收包有误
   *                 A:Merge error:Not same finger.合并错误:非同一手指
   */
  int8_t cmdRegModel();

  /**
   * @brief Delete all models.
   * @brief 删除指纹模块里的所有指纹模版
   *
   * @return int8_t -1:Failed.收包失败
   *                 0:Succeeded.成功
   *                 1:Pack error.收包有误
   *                11:Empty failed.清空失败
   */
  int8_t cmdEmpty();

  /**
   * @brief Save fingerprint from buffer to page.
   * @brief 将缓冲区中的特征码存放到指定的位置
   *
   * @param bufferID 缓冲区号
   * @param pageID 指纹库位置
   * @return int8_t -1:Failed.收包失败
   *                 0:Succeeded.成功
   *                 1:Pack error.收包有误
   *                 B:PageID out of range.超出指纹库范围
   *                 18:Flash error.写 Flash 出错
   */
  int8_t cmdSaveFinger(uint8_t bufferID, uint16_t pageID);

  /**
   * @brief Search fingerprint among pages.
   * @brief 从指纹库中搜索指纹
   *
   * @param bufferID 缓冲区号
   * @param startPageID 指纹库起始页
   * @param pageNum 页数
   * @return int8_t -1:Failed.收包失败
   *                 0:Finished.搜索完成
   *                 1:Pack error.收包有误
   *                 9:Nothing matched.未搜索到
   */
  int8_t cmdSearch(uint8_t bufferID, uint16_t startPageID, uint16_t pageNum);

  /**
   * @brief Delete models.
   * @brief 删除指纹模块里的指定指纹模版
   *
   * @param startPageID 指纹库起始页
   * @param pageNum 页数
   * @return int8_t -1:Failed.收包失败
   *                 0:Succeeded.成功
   *                 1:Pack error.收包有误
   *                10:Delete failed.删除失败
   */
  int8_t cmdDeleteModel(uint16_t startPageID, uint16_t pageNum);
};

#endif
