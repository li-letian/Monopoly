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
		pRet->name_ = std::string("石油公司");
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
			pop->setContent(StringUtils::format("你需要向董事长%s缴纳车辆燃油费用%d", owner->getPlayerName().c_str(), oil_value));
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