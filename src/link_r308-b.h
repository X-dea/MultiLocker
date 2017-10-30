/**
* MultiLocker (GPLv3)
* Support by CTBeta Team http://ctbeta.org/
* Created by Jason C.H Feb. 2017
*/

#ifndef LINK_R308_H
#define LINK_R308_H

class R308 {
private:
  void saveFingerId(int ID_temp);

public:
  R308();
  //~R308();
  void setupMode();
  bool searchFinger();
};

#endif
