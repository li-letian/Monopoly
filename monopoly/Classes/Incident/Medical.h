#ifndef _MEDICAL_H_
#define _MEDICAL_H_

#include "Character/Character.h"
#include "Scene/MapScene.h"

//�ͽ�ҽԺ
bool SendToHospital(Character* character);
//�������м����Ժ�����ѳ�Ժ�ĶԻ���
void PopUpHospitalDialog(Character* character, MapScene* map_scene);

#endif