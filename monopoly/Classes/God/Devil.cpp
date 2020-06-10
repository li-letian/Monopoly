#include "God/Devil.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"

Devil::Devil()
	:God("Devil")
{

}

bool Devil::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	initGodImage();
	this->setTag(devil);
	return true;
}

bool Devil::onLand(Character* standing)
{
	if (removeGodFromMap(standing))
	{
		standing->setGodPossessed(devil);
		GetGameController()->updateGod(devil);
		auto god_possessed = Devil::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Devil");
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}