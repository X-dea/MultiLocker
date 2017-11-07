/*!
   \file CTB_R308_act.cpp
   \brief CTBeta R308 Library (GPLv3) Support by CTBeta Team http://ctbeta.org/
   \author Jason C.H
   \date Nov. 2017

   A library for R308 fingerprint module.\n
   一个R308指纹模块库。
*/

#include <CTB_R308.h>

R308_act::R308_act() {}

/*!
   \brief Record fingerprint automatically.
   \brief 自动录制指纹
   \param PageID(指纹库位置)
   \return true(成功)/false(失败)
*/
bool R308_act::actRecordFinger(uint16_t pageID) {
  short sum = 0;
  sum += cmdGetImg();
  sum += cmdToBuffer1();
  sum += cmdGetImg();
  sum += cmdToBuffer2();
  sum += cmdRegModel();
  sum += cmdSaveFinger(1, pageID);
  if (sum == 0)
    return true;
  else
    return false;
}
