/*!
   \file link_rc522.cpp
   \brief RC522 controller Support by CTBeta Team http://ctbeta.org/
   \author Jason C.H
   \date Feb. 2017

   A controller of RC522.<br />
   一个RC522_RFID控制器。
*/

#include "config.h"
#include "link_rc522.h"

#ifdef USE_LOCAL
#include "local.h"
#endif

RFID rc522(PIN_SS, PIN_RFID_RST);
unsigned char status;
unsigned char str[MAX_LEN];
unsigned char RC_size;
unsigned char blockAddr;
unsigned char serNum[5];

RC522::RC522() {
  SPI.begin();
  rc522.init();
};

/*!
   \brief Find ID Card.
   \brief 寻找ID卡
   \return 读取序列号成功返回ture 失败返回false
*/
bool RC522::findCard() {
  rc522.init();
  rc522.isCard();
  return rc522.readCardSerial();
}

/*!
   \brief authid
   \brief 认证卡ID
   \return 成功返回ture 失败返回false
*/
bool RC522::authId() {
  int temp = 0;
  for (int a = 0; a <= local.maxidno - 1; a++) {
    temp = 0;
    for (int b = 0; b <= 4; b++) {
      if (local.IDList[a][b] == rc522.serNum[b])
        temp += 1;
    }
    if (temp == 5) {
      return true;
    }
  }
  return false;
}

/*!
   \brief authkey
   \brief 认证卡密钥
   \return 成功返回ture 失败返回false
*/
bool RC522::authKey() {
  int temp = 0;
  blockAddr = 16;
  status = rc522.auth(PICC_AUTHENT1A, 19, local.sectorKey[blockAddr / 4],
                      rc522.serNum);
  if (status == MI_OK) //认证区块
  {
    //读数据
    if (rc522.read(blockAddr, str) == MI_OK) {
      for (int i = 0; i <= 15; i++) {
        if (str[i] == local.authKey[0][i])
          temp += 1;
      }
      if (temp == 16)
        return true;
      else
        return false;
    }
  }
}
