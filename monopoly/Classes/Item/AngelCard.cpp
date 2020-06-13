#include "AngelCard.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void AngelCard::work(Character* player) {

	UseAngelCard(player->getCurPos());

}

bool AngelCard::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "��ʹ��";
	content_ = "��ǰ���ڽֵ������ù����������";
	return true;
}