/*!
   \file CTB_R308.h
   \brief CTBeta R308 Library (GPLv3) Support by CTBeta Team http://ctbeta.org/
   \author Jason C.H
   \date Nov. 2016

   A library for R308 fingerprint module.<br />
   一个R308指纹模块库。
*/

#ifndef CTB_R308_H
#define CTB_R308_H

#include <Arduino.h>

class CTB_R308 {

public:
  unsigned char packSerialRead[10]; ///<Origin retuens. 读取的返回数据

  CTB_R308();
  bool init();

  short cmdGetImg();
  short cmdToBuffer1();
  short cmdToBuffer2();
  short cmdRegModel();
  short cmdEmpty();
  short cmdSaveFinger(unsigned short ID_temp);
  short cmdSearch();
  short cmdDeleteModel(unsigned short ID_temp);

private:
  static unsigned char packHead[6] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF};
  static unsigned char packInit[10] = {0x01, 0x00, 0x07, 0x13, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x1B};
  static unsigned char packGetImg[6] = {0x01, 0x00, 0x03, 0x01, 0x0, 0x05};
  static unsigned char packToBuffer1[7] = {0x01, 0x0, 0x04, 0x02,
                                           0x01, 0x0, 0x08};
  static unsigned char packToBuffer2[7] = {0x01, 0x0, 0x04, 0x02,
                                           0x02, 0x0, 0x09};
  static unsigned char packRegModel[6] = {0x01, 0x0, 0x03, 0x05, 0x0, 0x09};
  static unsigned char packEmpty[6] = {0x01, 0x0, 0x03, 0x0d, 0x00, 0x11};

  /*!
    Save fingerprint from buffer to page.从指定缓冲区保存指纹
    sign  | length | command | bufferID | pageID | sum
    1byte | 2byte  | 1byte   | 1byte    | 2byte  | 2byte
  */
  unsigned char packSaveFinger[9] = {0x01, 0x00, 0x06, 0x06, 0x01,
                                     0x00, 0x02, 0x0,  0x0};
  /*!
    Search fingerprint among pages.从指纹库中搜索
    sign  | length | command | bufferID | start | end   | sum
    1byte | 2byte  | 1byte   | 1byte    | 2byte | 2byte | 2byte
  */
  unsigned char packSearch[11] = {0x01, 0x0,  0x08, 0x04, 0x01, 0x0,
                                  0x0,  0x01, 0xF4, 0x01, 0x03};

  /*!
    Delete N fingerprints from a pageID.从指定pageID删除N个指纹
    sign  | length | command | pageID | N     | sum
    1byte | 2byte  | 1byte   | 2byte  | 2byte | 2byte
  */
  unsigned char packDeleteModel[10] = {0x01, 0x00, 0x07, 0x0C, 0x0,
                                       0x0,  0x0,  0x1,  0x0,  0x0};

  void serialClean();
  bool serialRead();
};
#endif
