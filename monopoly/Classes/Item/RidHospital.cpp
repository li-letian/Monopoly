#include "RidHospital.h"
#include "Character/Character.h"
#include "Incident/Staff.h"

void RidHospital::worked(Character* player) {


}

bool RidHospital::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "出院证明";
	content_ = "给一个人办理出院手续，被动触发，点击确认则作废";
	return true;
}