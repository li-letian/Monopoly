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
	name_ = "�Ǽۿ�";
	content_ = "�õ�ǰ�Ľ�����·���Ǽ�";
	return true;
}