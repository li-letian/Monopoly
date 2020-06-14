#include "Stop.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void Stop::work(Character* player) {

	UseStayCard(player);

}

bool Stop::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "停留卡";
	content_ = "原地停留一回合";
	return true;
}