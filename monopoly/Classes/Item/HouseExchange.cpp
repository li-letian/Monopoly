#include "HouseExchange.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void HouseExchange::work(Character* player) {

	UseHouseBuy(player);

}

bool HouseExchange::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "购地证明";
	content_ = "强行占领当前角色所在的土地";
	return true;
}