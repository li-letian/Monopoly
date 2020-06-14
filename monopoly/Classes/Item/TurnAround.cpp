#include "TurnAround.h"
#include "Incident/Staff.h"

void TurnAround::work(Character* player) {

	UseTurnAroundCard(player);

}

bool TurnAround::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "转向卡";
	content_ = "蓦然回首";
	return true;
}