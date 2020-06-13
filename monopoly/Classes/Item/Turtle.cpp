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
	name_ = "乌龟卡";
	content_ = "只走一步，可能会有额外惊喜哦！";
	return true;
}