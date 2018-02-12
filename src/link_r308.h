/*!
   \file link_r308.cpp
   \brief Linker for R308 Module
   \author Jason C.H
   \date Feb. 2018
*/

#ifndef LINK_R308_H
#define LINK_R308_H

#include <Arduino.h>

class LR308 {
private:
  void saveFingerId(unsigned short pageID);

public:
  LR308();

  bool searchFinger();
};

#endif
