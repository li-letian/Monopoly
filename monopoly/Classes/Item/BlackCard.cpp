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
	name_ = "�ڿ�";
	content_ = "���е������ֿ��Ӷ�û��T T";
	return true;
}