/**
* MultiLocker (GPLv3)
* Support by CTBeta Team http://ctbeta.org/
* Created by Jason C.H Sept. 2017
*/
#include <Arduino.h>
#include <U8glib.h>
#include "Config.h"
#include "display.h"

DISPLAY_TYPE u8g(U8G_I2C_OPT_NONE);

display::display(){

}

void display::init(){
#ifdef SCREEN_FLIP
  u8g.setRot180();
#endif
}
