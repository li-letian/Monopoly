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
	name_ = "�ȼٿ�";
	content_ = "������ô������ȥ����";
	return true;
}