/**
* MultiLocker (GPLv3)
* Support by CTBeta Team http://ctbeta.org/
* Created by Jason C.H Feb 2017
*/

#ifndef LINK_RC522_H
#define LINK_RC522_H

#include <RFID.h>
#include <SPI.h>

class RC522 {
private:
public:
  RC522();
  //~RC522();
  bool findCard();
  bool authId();
  bool authKey();
};

#endif
