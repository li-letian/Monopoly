#include "RedCard.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void RedCard::work(Character* player) {

	UseRedCard(player);

}

bool RedCard::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "ºì¿¨";
	content_ = "¹É¼Û±©ÕÇ";
	return true;
}