#include "DevilCard.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void DevilCard::work(Character* player) {

	UseDevilCard(player->getCurPos());

}

bool DevilCard::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "��ħ��";
	content_ = "��ǰ���ڽֵ������ùݱ��ݻ٣�";
	return true;
}