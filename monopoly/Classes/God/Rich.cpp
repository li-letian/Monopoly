#include "God/Rich.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Incident/PopUpLayer.h"

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
		auto god_possessed = Rich::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Rich",rich);
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}

void Rich::popUpDialog()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("财神生效");
	pop->setContent("本次过路费免除");
	pop->setCallBack([=](Ref* render) {
		SendMsg(msg_make_go_apper);
		});
	pop->setOnScene();
}