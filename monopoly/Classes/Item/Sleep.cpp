#include "Sleep.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void HolidayCard::work(Character* player) {

	UseHolidayCard(player);

}

bool HolidayCard::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "度假卡";
	content_ = "世界这么大，我想去看看";
	return true;
}