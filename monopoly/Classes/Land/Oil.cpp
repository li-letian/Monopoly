#include "Oil.h"
#include "cocos2d.h"
#include "Land.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Incident/Incident.h"

USING_NS_CC;

Oil* Oil::create(int index)
{
	auto pRet = new(std::nothrow) Oil();
	if (pRet && pRet->init())
	{
		auto map_scene = GetMapScene();
		pRet->index_ = index;
		pRet->name_ = std::string("ʯ�͹�˾");
		pRet->setAnchorPoint(Vec2(0.5f, 0.5f));
		pRet->setPosition(map_scene->pos(index));
		map_scene->getMap()->addChild(pRet, 1);
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}

}


bool Oil::onLand(Character* standing)
{
	Character* owner = nullptr;
	auto map_scene = GetMapScene();
	auto store = GetStockScene()->getStock().at(5)->getStore();
	int total = 0;
	auto size = store.size();
	for (decltype(size) i = 0; i < size; i++)
	{
		//log("store %d :%d", i, store[i]);
		if (store[i] > total)
		{
			total = store[i];
			auto  vec = GetGameController()->getCharacters();
			for (auto c : vec)
			{
				if (c->getTag() == i)
				{
					owner = c;
				}
			}
		}
	}
	if (!owner)
	{
		if (standing->getIsAI() == false)
		{
			auto pop = PopUpLayer::create();
			pop->setTitle(name_);
			pop->setContent("��Ҫ�����³��𣿿�칺�򱾹�˾�Ĺ�ƱŶ����ǰ�ֲ��������˻��Ϊ����˾�Ķ��³������й�˾����Ȩ");
			pop->setCallBack([=](Ref* ref) { SendMsg(msg_make_go_apper); });
			pop->setPosition(Vec2(0, 0));
			map_scene->addChild(pop, 51);
		}
	}
	else
	{
		if (owner != standing)
		{
			auto pop = PopUpLayer::create();
			pop->setTitle(name_);
			pop->setContent(StringUtils::format("����Ҫ���³�%s���ɳ���ȼ�ͷ���%d", owner->getPlayerName().c_str(), oil_value));
			pop->setCallBack([=](Ref* ref)
			{
				GoOnHoliday(standing);
				standing->setMoney(standing->getMoney() - oil_value);
				SendMsg(msg_make_go_apper);
			});
			pop->setOnScene(51);
		}
		else SendMsg(msg_make_go_apper);

	}
	return true;
}