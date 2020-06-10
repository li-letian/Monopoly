#include "Car.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void Car::work(Character* player) {

	SetFlyingShoes(player);

}

bool Car::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "飞速鞋";
	content_ = "根本停不下来！！";
	return true;
}