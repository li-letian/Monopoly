#ifndef _HOLIDAY_H_
#define _HOLIDAY_H_

#include "Character/Character.h"
#include "Scene/MapScene.h"

bool GoOnHoliday(Character* character);	//送去度假
void PopUpHolidayDialog(Character* character, MapScene* map_scene);	//弹出还有几天度假回来或者已度假回来的对话框

#endif