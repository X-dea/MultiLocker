#include <CTB_R308.h>

R308_act::R308_act() {}

bool R308_act::actRecordFinger(unsigned short bufferID, unsigned short pageID) {
  short sum = 0;
  sum += cmdGetImg();
  sum += cmdToBuffer1();
  sum += cmdGetImg();
  sum += cmdToBuffer2();
  sum += cmdRegModel();
  sum += cmdSaveFinger(bufferID, pageID);
  if (sum == 0)
    return true;
  else
    return false;
}
