/**
* MultiLocker (GPLv3)
* Support by CTBeta Team
* Created by Jason C.H Feb 2017
*/

#include <RFID.h>
#include "Config.h"
#include "Link_rc522.h"

#ifdef USE_LOCAL
  #include "local.h"
#endif

RFID Rc522(PIN_SS,PIN_RFID_RST);
unsigned char status;
unsigned char str[MAX_LEN];
unsigned char RC_size;
unsigned char blockAddr;
unsigned char serNum[5];

RC522::RC522(){
 SPI.begin();
 Rc522.init();
 Serial.begin(57600);
};

/**
* 函 数 名：findcard
* 功能描述：寻卡并读取序列号
* 输入参数：无
* 返 回 值：读取序列号成功返回ture 失败返回false
*/
bool RC522::findcard(){
  Rc522.init();
  Rc522.isCard();
  return Rc522.readCardSerial();
}

/**
* 函 数 名：authid
* 功能描述：认证卡ID
* 输入参数：无
* 返 回 值：成功返回ture 失败返回false
*/
bool RC522::authid(){
 int temp=0;
 for(int a=0;a<=local.maxidno-1;a++){
   temp=0;
   for(int b=0;b<=4;b++){
     if(local.IDList[a][b]==Rc522.serNum[b])
     temp+=1;
  }
  if(temp==5){
      return true;
  }
}
 return false;
}

/**
* 函 数 名：authkey
* 功能描述：认证卡密钥
* 输入参数：无
* 返 回 值：成功返回ture 失败返回false
*/
bool RC522::authkey(){
 int temp=0;
 blockAddr=16;
 status = Rc522.auth(PICC_AUTHENT1A,19,local.sectorKey[blockAddr/4], Rc522.serNum);
 if (status == MI_OK)  //认证区块
 {
   //读数据
   if(Rc522.read(blockAddr,str) == MI_OK){
   for(int i=0;i<=15;i++){
     if(str[i]==local.authKey[0][i])
     temp+=1;
   }
   if(temp==16)
     return true;
   else
     return false;
   }
 }
}
