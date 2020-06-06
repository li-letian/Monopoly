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

USING_NS_CC;

Chance* Chance::create(MapScene* map_scene, int index)
{
	auto pRet = new(std::nothrow) Chance();
	if (pRet && pRet->init())
	{
		auto tile_size = map_scene->getMap()->getTileSize();
		pRet->setMapScene(map_scene);
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
	auto pop = PopUpLayer::create();
	pop->setTitle(name_);
	std::string txt;
	std::function<void(Ref*)>fun;
	srand(static_cast<unsigned int>(time(nullptr)));
	auto pos = 0;
	switch (rand() % 6)
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
		txt = StringUtils::format("奖励地产最多的人:%s %d", GetMostEstate()->getPlayerName().c_str(), reward_estate_money);
		fun = [=](Ref* ref) {RewardMostEstate(GetMostEstate()); };
		break;
	case 4:
		txt = StringUtils::format("补助地产最少的人:%s %d", GetLeastEstate()->getPlayerName().c_str(), help_estate_money);
		fun = [=](Ref* ref) {HelpLeastEstate(GetLeastEstate()); };
		break;
	case 5:
		txt = StringUtils::format("奖励持有股票最多的人:%s %d", GetMostStock()->getPlayerName().c_str(), help_stock_money);
		fun = [=](Ref* ref) {RewardMostStock(GetMostStock()); };
		break;
	default:
		txt = "平静的一天，什么都没有发生";
		fun = [=](Ref* ref) {};
		break;
	}
	pop->setContent(txt);
	pop->setCallBack([=](Ref* ref) {fun(ref); SendMsg(msg_make_go_apper); });
	pop->setPosition(Vec2(0, 0));
	map_scene_->addChild(pop, 51);
	return true;
}