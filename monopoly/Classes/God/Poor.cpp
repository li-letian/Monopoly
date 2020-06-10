#include "God/Poor.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Incident/PopUpLayer.h"

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
		auto god_possessed = Poor::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Poor",poor);
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}

void Poor::popUpDialog()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("������Ч");
	pop->setContent("���ι�·�ѷ���");
	pop->setCallBack([=](Ref* render) {
		SendMsg(msg_make_go_apper);
		});
	pop->setOnScene();
}