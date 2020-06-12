#include "RisePrice.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void RisePrice::work(Character* player) {

	UseRisePriceCard(player->getCurPos());

}

bool RisePrice::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "涨价卡";
	content_ = "让当前的街区过路费涨价";
	return true;
}