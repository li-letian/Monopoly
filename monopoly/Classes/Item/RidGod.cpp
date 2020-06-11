
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
	auto map_scene = GetMapScene();
	God* god=nullptr;
	switch (character->getGodPossessed())
	{
	case angel:
		god = Angel::create();
		break;
	case devil:
		god = Devil::create();
		break;
	case earth:
		god = Earth::create();
		break;
	case luck:
		god = Luck::create();
		break;
	case poor:
		god = Poor::create();
		break;
	case rich:
		god = Rich::create();
		break;
	case unluck:
		god = Unluck::create();
		break;
	}
	game_controller->getGods().pushBack(god);
	map_scene->getMap()->addChild(god, 10);
	game_controller->updateGod(no_god);
	character->setGodPossessed(normal);
	character->removeChildByName("god", true);
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

