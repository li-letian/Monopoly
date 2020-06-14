#include "HouseDestory.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void HouseDestory::work(Character* player) {

	UseHouseDestroy(player->getCurPos());

}

bool HouseDestory::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "怪兽卡";
	content_ = "彻底摧毁当前位置的房屋";
	return true;
}