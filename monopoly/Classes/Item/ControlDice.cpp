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
	name_ = "ң������";
	content_ = "�����ƶ�����";
	return true;
}