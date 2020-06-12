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
	name_ = "恶魔卡";
	content_ = "当前所在街道所有旅馆被摧毁！";
	return true;
}