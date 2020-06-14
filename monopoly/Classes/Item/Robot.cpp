#include "Robot.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void Robot::work(Character* player) {

	UseRobot(player);

}

bool Robot::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "机器娃娃";
	content_ = "清除前方一段距离内的所有神灵";
	return true;
}

