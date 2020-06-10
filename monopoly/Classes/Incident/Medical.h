#ifndef _MEDICAL_H_
#define _MEDICAL_H_

#include "cocos2d.h"
USING_NS_CC;
class Character;

//送进医院
bool SendToHospital(Character* character);

//将一群人送进医院
bool SendToHospital(Character*user,Vector<Character*>characters_to_hospital);

//弹出还有几天出院或者已出院的对话框
void PopUpHospitalDialog(Character* character);

#endif