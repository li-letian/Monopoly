#include "God/Devil.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Incident/PopUpLayer.h"

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
		auto god_possessed = Devil::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Devil",devil);
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}

void Devil::popUpDialog()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("恶魔生效");
	pop->setContent("强制破坏一层楼");
	pop->setCallBack([=](Ref* render) {
		SendMsg(msg_make_go_apper);
		});
	pop->setOnScene();
}