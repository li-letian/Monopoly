#include "God/Rich.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"

Rich::Rich()
	:God("Rich")
{

}

bool Rich::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	initGodImage();
	this->setTag(rich);
	return true;
}

bool Rich::onLand(Character* standing)
{
	if (removeGodFromMap(standing))
	{
		standing->setGodPossessed(rich);
		GetGameController()->updateGod(rich);
		auto god_possessed = Rich::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Rich");
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}