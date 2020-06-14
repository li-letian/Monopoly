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
	name_ = "ͣ����";
	content_ = "ԭ��ͣ��һ�غ�";
	return true;
}