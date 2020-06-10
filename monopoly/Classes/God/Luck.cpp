#include "Luck.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Incident/PopUpLayer.h"

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
		auto god_possessed = Luck::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Luck",luck);
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}

void Luck::popUpDialog()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("福神生效");
	pop->setContent("免费加盖一层");
	pop->setCallBack([=](Ref* render) {
		SendMsg(msg_make_go_apper);
		});
	pop->setOnScene();
}