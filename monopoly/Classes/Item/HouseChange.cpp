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
	name_ = "����֤��";
	content_ = "������غ�����Ե�������ˣ�";
	return true;
}