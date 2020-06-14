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
	name_ = "天使卡";
	content_ = "当前所在街道所有旅馆免费升级！";
	return true;
}