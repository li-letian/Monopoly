#include "Turtle.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void Turtle::work(Character* player) {

	SetTurtle(player);

}

bool Turtle::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "�ڹ꿨";
	content_ = "ֻ��һ�������ܻ��ж��⾪ϲŶ��";
	return true;
}