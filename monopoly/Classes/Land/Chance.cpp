#include "Chance.h"
#include "cocos2d.h"
#include "Land.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Incident/Incident.h"
#include "Character/Character.h"
#include "Scene/ItemScene.h"
#include "Incident/Stay.h"

USING_NS_CC;

Chance* Chance::create(int index)
{
	auto pRet = new(std::nothrow) Chance();
	if (pRet && pRet->init())
	{
		auto map_scene = GetMapScene();
		auto tile_size = map_scene->getMap()->getTileSize();
		pRet->index_ = index;
		pRet->name_ = std::string("机会");
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


bool Chance::onLand(Character* standing)
{
	auto map_scene = GetMapScene();
	auto pop = PopUpLayer::create();
	pop->setTitle(name_);
	std::string txt;
	std::function<void(Ref*)>fun;
	srand(static_cast<unsigned int>(time(nullptr)));
	auto pos = 0;
	switch (rand() % 15)
	{
	case 0:
		pos = GetRandomHotel();
		txt = StringUtils::format("%d处整个街道房屋售价全线下降", pos);
		fun = [=](Ref* ref) {SellPriceDown(pos); };
		break;
	case 1:
		pos = GetRandomHotel();
		txt = StringUtils::format("%d处整个街道房屋过路费全线上涨", pos);
		fun = [=](Ref* ref) {RentPriceUp(pos); };
		break;
	case 2:
		txt = "股市全线上涨";
		fun = [=](Ref* ref) {StockMarketUp(); };
		break;
	case 3:
	{
		auto target = GetMostEstate();
		txt = StringUtils::format("奖励地产最多的人:%s %d", target->getPlayerName().c_str(), reward_estate_money);
		fun = [=](Ref* ref) {RewardMostEstate(target); };
		break;
	}
	case 4:
	{
		auto target = GetLeastEstate();
		txt = StringUtils::format("补助地产最少的人:%s %d", target->getPlayerName().c_str(), help_estate_money);
		fun = [=](Ref* ref) {HelpLeastEstate(target); };
		break;
	}
	case 5:
	{
		auto target = GetMostStock();
		txt = StringUtils::format("奖励持有股票最多的人:%s %d", target->getPlayerName().c_str(), reward_stock_money);
		fun = [=](Ref* ref) {RewardMostStock(target); };
		break;
	}
	default:
		txt = "恭喜你随机获得了一个道具";
		fun = [=](Ref* ref)
		{
			GetRandomItem(standing);
		};
		break;
	}
	pop->setContent(txt);
	pop->setCallBack([=](Ref* ref) {fun(ref); SendMsg(msg_make_go_apper); });
	pop->setOnScene(51);
	return true;
}