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
	name_ = "��������";
	content_ = "���ǰ��һ�ξ����ڵ���������";
	return true;
}

