#include "ControlDice.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void ControlDice::work(Character* player) {

	//UseControlDice(player);

}

bool ControlDice::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "遥控骰子";
	content_ = "决定移动步数";
	return true;
}