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
	name_ = "��Ժ֤��";
	content_ = "��һ���˰����Ժ����";
	return true;
}