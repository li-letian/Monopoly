#ifndef _MEDICAL_H_
#define _MEDICAL_H_

#include "cocos2d.h"
USING_NS_CC;
class Character;

//�ͽ�ҽԺ
bool SendToHospital(Character* character);

//��һȺ���ͽ�ҽԺ
bool SendToHospital(Character*user,Vector<Character*>characters_to_hospital);

//�������м����Ժ�����ѳ�Ժ�ĶԻ���
void PopUpHospitalDialog(Character* character);

#endif