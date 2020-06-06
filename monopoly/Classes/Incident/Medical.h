#ifndef _MEDICAL_H_
#define _MEDICAL_H_

#include "Character/Character.h"
#include "Scene/MapScene.h"

//送进医院
bool SendToHospital(Character* character);
//弹出还有几天出院或者已出院的对话框
void PopUpHospitalDialog(Character* character, MapScene* map_scene);

#endif