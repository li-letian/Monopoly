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

void Devil::popUpDialog()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("恶魔生效");
	pop->setContent("强制破坏一层楼");
	pop->setCallBack([=](Ref* render) {
		SendMsg(msg_make_go_appear);
		});
	pop->setOnScene();
}