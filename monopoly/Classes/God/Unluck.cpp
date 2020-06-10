#include "God/Unluck.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"

Unluck::Unluck()
	:God("Unluck")
{

}

bool Unluck::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	initGodImage();
	this->setTag(unluck);
	return true;
}

bool Unluck::onLand(Character* standing)
{
	if (removeGodFromMap(standing))
	{
		standing->setGodPossessed(unluck);
		GetGameController()->updateGod(unluck);
		auto god_possessed = Unluck::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Unluck");
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}