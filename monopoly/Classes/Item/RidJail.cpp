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
	name_ = "����֤��";
	content_ = "��һ���˰����ͣ��������������ȷ��������";
	return true;
}