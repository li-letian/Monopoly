
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
	//请神怎么写啊
}

bool Pray::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "请神符";
	content_ = "请来离自己步数最近的神灵";
	return true;
}

