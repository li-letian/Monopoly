#include "HouseChange.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void HouseChange::work(Character* player) {

	UseHouseBuy(player);

}

bool HouseChange::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "购地证明";
	content_ = "这块土地和我有缘，归我了！";
	return true;
}