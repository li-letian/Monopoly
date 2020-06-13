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
		pRet->name_ = std::string("保险公司");
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
			pop->setContent("想要当董事长吗？快快购买本公司的股票哦，当前持仓数最多的人会成为本公司的董事长，享有公司所有权");
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
			pop->setContent(StringUtils::format("你需要向董事长%s缴纳人寿保险%d,以后的10天内如果发生医疗事故，你会得到双倍的赔偿", owner->getPlayerName().c_str(), insurance_value));
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