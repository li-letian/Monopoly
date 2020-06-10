#include "God/Poor.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"

Poor::Poor()
	:God("Poor")
{

}

bool Poor::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	initGodImage();
	this->setTag(poor);
	return true;
}

bool Poor::onLand(Character* standing)
{
	if (removeGodFromMap(standing))
	{
		standing->setGodPossessed(poor);
		GetGameController()->updateGod(poor);
		auto god_possessed = Poor::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Poor");
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}