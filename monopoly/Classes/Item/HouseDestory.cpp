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
	name_ = "���޿�";
	content_ = "���״ݻٵ�ǰλ�õķ���";
	return true;
}