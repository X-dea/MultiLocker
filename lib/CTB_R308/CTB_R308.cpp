/**
* CTBeta R308 Library (GPLv3)
* Support by CTBeta Team http://www.ctbeta.org/
* Created by Jason C.H Nov 2016
*/

#include <Arduino.h>
#include <CTB_R308.h>

unsigned char FP_Init[]={0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1B};//模块握手验证
unsigned char FP_Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};  //协议包头
unsigned char FP_Get_Img[6] = {0x01,0x00,0x03,0x01,0x0,0x05};    //获得指纹图像
unsigned char FP_Templete_Num[6] ={0x01,0x00,0x03,0x1D,0x00,0x21 }; //获得模版总数
unsigned char FP_Search[11]={0x01,0x0,0x08,0x04,0x01,0x0,0x0,0x01,0xF4,0x0,0xB2}; //搜索指纹搜索范围0 - 929
//unsigned char FP_Search_0_9[11]={0x01,0x0,0x08,0x04,0x01,0x0,0x0,0x0,0x13,0x0,0x21}; //搜索0-9号指纹
unsigned char FP_Img_To_Buffer1[7]={0x01,0x0,0x04,0x02,0x01,0x0,0x08}; //将图像放入到BUFFER1
unsigned char FP_Img_To_Buffer2[7]={0x01,0x0,0x04,0x02,0x02,0x0,0x09}; //将图像放入到BUFFER2
unsigned char FP_Reg_Model[6]={0x01,0x0,0x03,0x05,0x0,0x09}; //将BUFFER1跟BUFFER2合成特征模版
unsigned char FP_Delet_All_Model[6]={0x01,0x0,0x03,0x0d,0x00,0x11};//删除指纹模块里所有的模版
unsigned char FP_Save_Finger[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//将BUFFER1中的特征码存放到指定的位置
unsigned char FP_Delete_Model[10]={0x01,0x00,0x07,0x0C,0x0,0x0,0x0,0x1,0x0,0x0}; //删除指定的模版
//volatile unsigned char FINGER_NUM;

unsigned char FP_SerialRead[10];

CTB_R308::CTB_R308()
{
}

/**
* 函 数 名：init
* 功能描述：初始化函数库，对指纹模块进行握手验证
* 输入参数：无
* 返 回 值：无
*/
bool CTB_R308::init()
{
  Serial.begin(57600);
  SerialClean();
  Serial.write(&FP_Pack_Head[0],6);
  Serial.write(&FP_Init[0],10);
  delay(100);
  return true;
 }
/**
* 函 数 名：Cmd_Get_Img
* 功能描述：获得指纹图像
* 输入参数：无
* 返 回 值：无
*/
 void CTB_R308::Cmd_Get_Img()
 {
  Serial.write(&FP_Pack_Head[0],6);
  Serial.write(&FP_Get_Img[0],6);
 }

/**
* 函 数 名：Cmd_Img_To_Buffer1
* 功能描述：将图像转换成特征码存放在Buffer1中
* 输入参数：无
* 返 回 值：无
*/
void CTB_R308::Cmd_Img_To_Buffer1()
{
  Serial.write(&FP_Pack_Head[0],6);
  Serial.write(&FP_Img_To_Buffer1[0],7);
}

/**
* 函 数 名：Cmd_Img_To_Buffer2
* 功能描述：将图像转换成特征码存放在Buffer2中
* 输入参数：无
* 返 回 值：无
*/
void CTB_R308::Cmd_Img_To_Buffer2()
{
  Serial.write(&FP_Pack_Head[0],6);
  Serial.write(&FP_Img_To_Buffer2[0],7);
}

/**
* 函 数 名：Cmd_Reg_Model
* 功能描述：将BUFFER1 跟 BUFFER2 中的特征码合并成指纹模版
* 输入参数：无
* 返 回 值：无
*/
void CTB_R308::Cmd_Reg_Model()
{
  Serial.write(&FP_Pack_Head[0],6);
  Serial.write(&FP_Reg_Model[0],6);
}

/**
* 函 数 名：Cmd_Delete_All_Model
* 功能描述：删除指纹模块里的所有指纹模版
* 输入参数：无
* 返 回 值：无
*/
void CTB_R308::Cmd_Delete_All_Model()
{
  Serial.write(&FP_Pack_Head[0],6);
  Serial.write(&FP_Delet_All_Model[0],6);
}

/**
* 函 数 名：Cmd_Delete_Model
* 功能描述：删除指纹模块里的指定指纹模版
* 输入参数：指纹ID
* 返 回 值：无
*/
void CTB_R308::Cmd_Delete_Model(unsigned int ID_temp)
{
  volatile unsigned int Sum_temp = 0;

  FP_Delete_Model[4]=(ID_temp&0xFF00)>>8;
  FP_Delete_Model[5]=(ID_temp&0x00FF);

  for(int i=0;i<8;i++)
      Sum_temp = Sum_temp + FP_Delete_Model[i];

  FP_Delete_Model[8]=(Sum_temp&0xFF00)>>8;
  FP_Delete_Model[9]=Sum_temp&0x00FF;

  Serial.write(&FP_Pack_Head[0],6);
  Serial.write(&FP_Delete_Model[0],10);
}

/**
* 函 数 名：Cmd_Search_Finger
* 功能描述：搜索全部用户
* 输入参数：无
* 返 回 值：无
*/
void CTB_R308::Cmd_Search_Finger()
{
  Serial.write(&FP_Pack_Head[0],6);
  Serial.write(&FP_Search[0],11);
}

/**
* 函 数 名：SerialClean
* 功能描述：清空串口缓存
* 输入参数：无
* 返 回 值：无
*/
void CTB_R308::SerialClean()
{
  while(Serial.read() >= 0){}
}

/**
* 函 数 名：SerialRead
* 功能描述：进行串口返回读取
* 输入参数：无
* 返 回 值：指令码
*/
bool CTB_R308::SerialRead()
{
  //等待应答 wait for reaction
  while (Serial.available()<=0){}
  //验证模块地址和应答包 module id auth
  if (Serial.read()==0xEF && Serial.read()==0x01)
  {
    for(int i=0;i<4;i++)
    {
      if (Serial.read()!=FP_Pack_Head[i+2])
      return false;
    }
    if (Serial.read()!=0x07) return false;
  }else return false;
  //接收包
  FP_SerialRead[0]=Serial.read();
  for (int i=1;i<=FP_SerialRead[0];i++)
    FP_SerialRead[i]=Serial.read();
  return true;
}
