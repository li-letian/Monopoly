#include "Sleep.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void Sleep::work(Character* player) {

	UseHolidayCard(player);

}

bool Sleep::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "�ȼٿ�";
	content_ = "������ô������ȥ����";
	return true;
}