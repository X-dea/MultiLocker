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

class CTB_R308

{

public:
  unsigned char FP_SerialRead[10]; ///<Origin retuens. 读取的返回数据

  CTB_R308();
  bool init();

  bool cmdGetImg();
  bool cmdToBuffer1();
  bool cmdToBuffer2();
  bool cmdRegModel();
  bool cmdSaveFinger(unsigned int ID_temp);
  bool cmdDeleteAll();
  bool cmdDeleteModel(unsigned int ID_temp);
  bool cmdSearch();

private:
  unsigned char packHead[6] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF};
  unsigned char packInit[10] = {0x01, 0x00, 0x07, 0x13, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x1B};
  unsigned char packGetImg[6] = {0x01, 0x00, 0x03, 0x01, 0x0, 0x05};
  //获得指纹图像
  unsigned char packSearch[11] = {0x01, 0x0,  0x08, 0x04, 0x01, 0x0,
                                  0x0,  0x01, 0xF4, 0x01, 0x03};
  //搜索指纹搜索范围0 - 929
  unsigned char packToBuffer1[7] = {0x01, 0x0, 0x04, 0x02, 0x01, 0x0, 0x08};
  //将图像放入到BUFFER1
  unsigned char packToBuffer2[7] = {0x01, 0x0, 0x04, 0x02, 0x02, 0x0, 0x09};
  //将图像放入到BUFFER2
  unsigned char packRegModel[6] = {0x01, 0x0, 0x03, 0x05, 0x0, 0x09};
  //将BUFFER1跟BUFFER2合成特征模版
  unsigned char packDeletAll[6] = {0x01, 0x0, 0x03, 0x0d, 0x00, 0x11};
  //删除指纹模块里所有的模版
  unsigned char packSaveFinger[9] = {0x01, 0x00, 0x06, 0x06, 0x01,
                                     0x00, 0x02, 0x0,  0x0};
  //将BUFFER1中的特征码存放到指定的位置
  unsigned char packDeleteModel[10] = {0x01, 0x00, 0x07, 0x0C, 0x0,
                                       0x0,  0x0,  0x1,  0x0,  0x0};
  //删除指定的模版
  // unsigned char FP_Templete_Num[6]={0x01,0x00,0x03,0x1D,0x00,0x21};
  // //获得模版总数
  // unsigned char

  void serialClean();
  bool serialRead();
};

#endif
