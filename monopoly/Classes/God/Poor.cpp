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

void Poor::popUpDialog()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("穷神生效");
	pop->setContent("本次过路费翻倍");
	pop->setCallBack([=](Ref* render) {
		SendMsg(msg_make_go_appear);
		});
	pop->setOnScene();
}