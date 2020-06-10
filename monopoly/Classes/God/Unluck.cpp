#include "God/Unluck.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Incident/PopUpLayer.h"

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
		auto god_possessed = Unluck::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Unluck",unluck);
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}

void Unluck::popUpDialog()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("˥����Ч");
	pop->setContent("Ͷ��ʧ��");
	pop->setCallBack([=](Ref* render) {
		SendMsg(msg_make_go_apper);
		});
	pop->setOnScene();
}