#include "RidJail.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void RidJail::worked(Character* player) {

	

}

bool RidJail::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "保释证明";
	content_ = "给一个人办理保释，被动触发，点击确认则作废";
	return true;
}