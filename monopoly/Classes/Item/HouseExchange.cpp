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
	name_ = "����֤��";
	content_ = "ǿ��ռ�쵱ǰ��ɫ���ڵ�����";
	return true;
}