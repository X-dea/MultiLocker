/*!
   \file link_rc522.h
   \brief Linker for RC522 Module
   \author Jason C.H
   \date Feb. 2017
*/

#ifndef LINK_RC522_H
#define LINK_RC522_H

#include <RFID.h>
#include <SPI.h>

class RC522 {
private:
public:
  RC522();

  /*!
     \brief Find ID Card.
     \brief 寻找ID卡
     \return 读取序列号成功返回ture 失败返回false
  */
  bool findCard();
  bool authId();
  bool authKey();
};

#endif
