#include "BlackCard.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void BlackCard::work(Character* player) {

	UseBlackCard(player);

}

bool BlackCard::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "黑卡";
	content_ = "股市跌到对手裤子都没了T T";
	return true;
}