#ifndef _HOLIDAY_H_
#define _HOLIDAY_H_

#include "Character/Character.h"
#include "Scene/MapScene.h"

//��ȥ�ȼ�
bool GoOnHoliday(Character* character);
//�������м���ȼٻ��������Ѷȼٻ����ĶԻ���
void PopUpHolidayDialog(Character* character, MapScene* map_scene);

#endif