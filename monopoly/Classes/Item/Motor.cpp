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
	name_ = "远行鞋";
	content_ = "飞一般的感觉！！";
	return true;
}