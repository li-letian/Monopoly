#include "Luck.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"

Luck::Luck()
	:God("Luck")
{

}

bool Luck::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	initGodImage();
	this->setTag(luck);
	return true;
}

bool Luck::onLand(Character* standing)
{
	if (removeGodFromMap(standing))
	{
		standing->setGodPossessed(luck);
		GetGameController()->updateGod(luck);
		auto god_possessed = Luck::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Luck");
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}