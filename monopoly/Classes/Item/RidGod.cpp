
#include "RidGod.h"
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

void RidGod::work(Character* character) {
	if (character->getGodPossessed() == normal) return;
	auto game_controller = GetGameController();

	character->setGodTimes(0);
	character->setGodPossessed(normal);
	game_controller->getGods().pushBack(dynamic_cast<God*>(character->getChildByName("god")));
	character->removeChildByName("god", true);
	game_controller->updateGod(no_god);
}

bool RidGod::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "送神符";
	content_ = "送走附身的神灵";
	return true;
}

