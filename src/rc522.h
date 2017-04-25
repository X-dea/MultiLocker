/*
 * MultiLockers (GPLv3)
 * Support by CTBeta Team
 * Created by Jason C.H Feb 2017
 * 整理者：Jason C.H
 * 整理时间：2017.2.26
 */

#ifndef RC522_H
#define RC522_H

#include <RFID.h>
#include <SPI.h>

class RC522 {
private:

public:

  RC522();
  bool findcard();
  bool authid();
  bool authkey();

};

#endif
