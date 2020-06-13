#include "Insurance.h"
#include "cocos2d.h"
#include "Land.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "Scene/StockScene.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Incident/Incident.h"

USING_NS_CC;

Insurance* Insurance::create(int index)
{
	auto pRet = new(std::nothrow) Insurance();
	if (pRet && pRet->init())
	{
		auto map_scene = GetMapScene();
		auto tile_size = map_scene->getMap()->getTileSize();
		pRet->index_ = index;
		pRet->name_ = std::string("���չ�˾");
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


bool Insurance::onLand(Character* standing)
{
	auto map_scene = GetMapScene();
	Character* owner = nullptr;
	auto store = GetStockScene()->getStock().at(4)->getStore();
	int total = 0;
	int size = store.size();
	for (int i=0;i<size;i++)
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
			pop->setContent(StringUtils::format("����Ҫ���³�%s�������ٱ���%d,�Ժ��10�����������ҽ���¹ʣ����õ�˫�����⳥", owner->getPlayerName().c_str(), insurance_value));
			pop->setCallBack([=](Ref* ref)
			{
				standing->setInsurance(10);
				standing->setMoney(standing->getMoney() - insurance_value);
				SendMsg(msg_make_go_apper);
			});
			pop->setOnScene();
		}
		else SendMsg(msg_make_go_apper);
		
	}
	return true;
}