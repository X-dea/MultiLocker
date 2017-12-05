/**
* MultiLocker (GPLv3)
* Support by CTBeta Team http://ctbeta.org/
* Created by Jason C.H Feb. 2017
*/

#ifndef LINK_R308_H
#define LINK_R308_H

class LR308 {
private:
  void saveFingerId(unsigned short pageID);

public:
  LR308();

  bool searchFinger();
};

#endif
