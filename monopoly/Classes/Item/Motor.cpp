#include "Motor.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void Motor::work(Character* player) {

	SetSpeedShoes(player);

}

bool Motor::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "Զ��Ь";
	content_ = "��һ��ĸо�����";
	return true;
}