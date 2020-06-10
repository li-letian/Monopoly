#include "God/Angel.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"

Angel::Angel()
	:God("Angel")
{

}

bool Angel::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	initGodImage();
	this->setTag(angel);
	return true;
}

bool Angel::onLand(Character* standing)
{
	if (removeGodFromMap(standing))
	{
		standing->setGodPossessed(angel);
		GetGameController()->updateGod(angel);
		auto god_possessed = Angel::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Angel");
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}