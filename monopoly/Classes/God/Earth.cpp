#include "God/Earth.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"

Earth::Earth()
	:God("Earth")
{
	
}

bool Earth::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	initGodImage();
	this->setTag(earth);
	return true;
}

bool Earth::onLand(Character* standing)
{
	if (removeGodFromMap(standing))
	{
		standing->setGodPossessed(earth);
		GetGameController()->updateGod(earth);
		auto god_possessed = Earth::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Earth");
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}

