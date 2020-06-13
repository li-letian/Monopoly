#include "RedCard.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void RedCard::work(Character* player) {

	UseRedCard(player);

}

bool RedCard::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "�쿨";
	content_ = "�ɼ۱���";
	return true;
}