#ifndef _MEDICAL_H_
#define _MEDICAL_H_

#include "Character/Character.h"
#include "Scene/MapScene.h"

bool SendToHospital(Character* character);	//�ͽ�ҽԺ
void PopUpHospitalDialog(Character* character, MapScene* map_scene);	//�������м����Ժ�����ѳ�Ժ�ĶԻ���

#endif