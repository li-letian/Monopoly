#include "God/MinePosition.h"
#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"
#include "Incident/PopUpLayer.h"
#include "Incident/Medical.h"

MinePosition::MinePosition()
	:God("MinePosition")
{

}

bool MinePosition::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	initGodImage();
	this->setTag(mine_position);
	return true;
}

bool MinePosition::onLand(Character* standing)
{
	if (standing->getCondition() == normal)
	{
		this->removeFromParentAndCleanup(true);
		auto pop = PopUpLayer::create();
		pop->setTitle("���ױ�ը");
		pop->setContent(standing->getPlayerName() + std::string("�ȵ��˵��ף���ը��סԺ"));
		pop->setCallBack([=](Ref* render) {
			SendToHospital(standing);
			SendMsg(msg_make_go_apper);
			});
		pop->setOnScene();
		return true;
	}
	else
	{
		return false;
	}
}
