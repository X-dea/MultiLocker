/**
* MultiLocker (GPLv3)
* Support by CTBeta Team
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
  bool findcard();
  bool authid();
  bool authkey();

};

#endif
