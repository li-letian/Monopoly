#include "TurnAround.h"
#include "Incident/Staff.h"

void TurnAround::work(Character* player) {

	UseTurnAroundCard(player);

}

bool TurnAround::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "ת��";
	content_ = "��Ȼ����";
	return true;
}