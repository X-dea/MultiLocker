/**
* CTBeta R308 Library (GPLv3)
* Support by CTBeta Team http://www.ctbeta.org/
* Created by Jason C.H Nov 2016
*/

#ifndef  CTB_R308_H
#define CTB_R308_H

class CTB_R308

{

public:

	CTB_R308();
	bool init();
	void Cmd_Get_Img();
	void Cmd_Img_To_Buffer1();
  void Cmd_Img_To_Buffer2();
  void Cmd_Reg_Model();
  void Cmd_Delete_All_Model();
  void Cmd_Delete_Model(unsigned int ID_temp);
  void Cmd_Search_Finger();

private:
	void SerialClean();
	bool SerialRead();

};

#endif
