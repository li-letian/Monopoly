#include "God/Angel.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Incident/PopUpLayer.h"

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
		auto god_possessed = Angel::create();
		addToCharacter(god_possessed, standing);
		popUpExplain("Angel",angel);
		return true;
	}
	else
	{
		GetGameController()->dealWithLand();
		return true;
	}
}

void Angel::popUpDialog()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("天使生效");
	pop->setContent("众生平等，加盖一层楼");
	pop->setCallBack([=](Ref* render) {
		SendMsg(msg_make_go_apper);
	});
	pop->setOnScene();
}