#ifndef _CHRIMINAL_H_
#define _CHRIMINAL_H_

#include "Character/Character.h"
#include "Scene/MapScene.h"

//�͵�����
bool SendToJail(Character* character);

//�������м�����������ѳ����ĶԻ���
void PopUpJailDialog(Character* character, MapScene* map_scene);

#endif