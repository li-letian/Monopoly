
#include "Pray.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Incident/PopUpLayer.h"
#include "Scene/GameController.h"
#include "Common/CommonConstant.h"
#include "God/Angel.h"
#include "God/Devil.h"
#include "God/Earth.h"
#include "God/Luck.h"
#include "God/Poor.h"
#include "God/Rich.h"
#include "God/Unluck.h"

void Pray::work(Character* character) {
	//������ôд��
}

bool Pray::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "�����";
	content_ = "�������Լ��������������";
	return true;
}

