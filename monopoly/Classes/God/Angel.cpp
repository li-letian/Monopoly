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

void Angel::popUpDialog()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("��ʹ��Ч");
	pop->setContent("����ƽ�ȣ��Ӹ�һ��¥");
	pop->setCallBack([=](Ref* render) {
		SendMsg(msg_make_go_appear);
	});
	pop->setOnScene();
}