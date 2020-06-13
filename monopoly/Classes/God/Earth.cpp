#include "God/Earth.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Incident/PopUpLayer.h"

Earth::Earth()
	:God("Earth")
{
	
}

bool Earth::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	initGodImage();
	this->setTag(earth);
	return true;
}

void Earth::popUpDialog()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("���ع���Ч");
	pop->setContent("ǿռ��������");
	pop->setCallBack([=](Ref* render) {
		SendMsg(msg_make_go_apper);
		});
	pop->setOnScene();
}
