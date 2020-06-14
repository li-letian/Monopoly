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

#include "Item/AngelCard.h"
#include "Item/ControlDice.h"
#include "Item/HouseChange.h"
#include "Item/Item.h"
#include "Item/Pray.h"
#include "Item/RidHospital.h"
#include "Item/Sleep.h"
#include "Item/Turtle.h"
#include "Item/Average.h"
#include "Item/DevilCard.h"
#include "Item/HouseDestory.h"
#include "Item/Mine.h"
#include "Item/RedCard.h"
#include "Item/RidJail.h"
#include "Item/Stop.h"
#include "Item/Sleep.h"
#include "Item/Worker.h"
#include "Item/BlackCard.h"
#include "Item/Escape.h"
#include "Item/HouseExchange.h"
#include "Item/Missile.h"
#include "Item/Revenge.h"
#include "Item/RisePrice.h"
#include "Item/Transmit.h"
#include "Item/Car.h"
#include "Item/Frame.h"
#include "Item/Impute.h"
#include "Item/Motor.h"
#include "Item/RidGod.h"
#include "Item/Robot.h"
#include "Item/TurnAround.h"

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
			switch (rand() % 29)
			{
			case	0:	GetItemScene()->addItem(standing, AngelCard::create());	break;
			case	1:	GetItemScene()->addItem(standing, ControlDice::create());	break;
			case	2:	GetItemScene()->addItem(standing, HouseChange::create());	break;
			case	3:	GetItemScene()->addItem(standing, Pray::create());	break;
			case	4:	GetItemScene()->addItem(standing, RidHospital::create());	break;
			case	5:	GetItemScene()->addItem(standing, Sleep::create());	break;
			case	6:	GetItemScene()->addItem(standing, Turtle::create());	break;
			case	7:	GetItemScene()->addItem(standing, Average::create());	break;
			case	8:	GetItemScene()->addItem(standing, DevilCard::create());	break;
			case	9:	GetItemScene()->addItem(standing, HouseDestory::create());	break;
			case	10:	GetItemScene()->addItem(standing, Mine::create());	break;
			case	11:	GetItemScene()->addItem(standing, RedCard::create());	break;
			case	12:	GetItemScene()->addItem(standing, RidJail::create());	break;
			case	13:	GetItemScene()->addItem(standing, Stop::create());	break;
			case	14:	GetItemScene()->addItem(standing, Worker::create());	break;
			case	15:	GetItemScene()->addItem(standing, BlackCard::create());	break;
			case	16:	GetItemScene()->addItem(standing, Escape::create());	break;
			case	17:	GetItemScene()->addItem(standing, HouseExchange::create());	break;
			case	18:	GetItemScene()->addItem(standing, Missile::create());	break;
			case	19:	GetItemScene()->addItem(standing, Revenge::create());	break;
			case	20:	GetItemScene()->addItem(standing, RisePrice::create());	break;
			case	21:	GetItemScene()->addItem(standing, Transmit::create());	break;
			case	22:	GetItemScene()->addItem(standing, Car::create());	break;
			case	23:	GetItemScene()->addItem(standing, Frame::create());	break;
			case	24:	GetItemScene()->addItem(standing, Impute::create());	break;
			case	25:	GetItemScene()->addItem(standing, Motor::create());	break;
			case	26:	GetItemScene()->addItem(standing, RidGod::create());	break;
			case	27:	GetItemScene()->addItem(standing, Robot::create());	break;
			case	28:	GetItemScene()->addItem(standing, TurnAround::create());	break;
			default:
				break;
			}
		};
		break;
	}
	pop->setContent(txt);
	pop->setCallBack([=](Ref* ref) {fun(ref); SendMsg(msg_make_go_apper); });
	pop->setOnScene(51);
	return true;
}