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
	name_ = "����Ь";
	content_ = "����ͣ����������";
	return true;
}