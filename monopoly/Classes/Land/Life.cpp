#include "Life.h"
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

Life* Life::create(MapScene* map_scene, int index)
{
	auto pRet = new(std::nothrow) Life();
	if (pRet && pRet->init())
	{
		auto tile_size = map_scene->getMap()->getTileSize();
		pRet->setMapScene(map_scene);
		pRet->index_ = index;
		pRet->name_ = std::string("命运");
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


bool Life::onLand(Character* standing)
{
	auto pop= PopUpLayer::create();
	pop->setTitle(name_);
	std::string txt;
	std::function<void(Ref*)>fun;
	srand(static_cast<unsigned int>(time(nullptr)));
	auto pos = 0;
	switch (rand()%15)
	{
	case 0:
		txt = "遭遇车祸，加速鞋被毁";
		fun = [=](Ref* ref) {DestroySpecialShoes(standing); };
		break;
	case 1:
		pos = GetRandomHotel();
		txt = StringUtils::format("%d处整个街道房屋售价全线上涨", pos);
		fun = [=](Ref* ref) {SellPriceRise(pos); };
		break;
	case 2:
		pos = GetRandomHotel();
		txt = StringUtils::format("%d处整个街道房屋过路费全线下降", pos);
		fun = [=](Ref* ref) {RentPriceDown(pos); };
		break;
	case 3:
		txt = "山体滑坡导致某地房屋被彻底摧毁";
		fun = [=](Ref* ref) {DestroyOneRandomHouse(); };
		break;
	case 4:
		txt = "地震导致某条街房屋整个被摧毁";
		fun = [=](Ref* ref) {DestroyOneRandomStreetHouse(); };
		break;
	case 5:
		txt = "UFO降临，你的某座房屋摧毁";
		fun = [=](Ref* ref) {DestroyOneCertainHouse(standing); };
		break;
	case 6:
		txt = "政府随机征收你的一片土地";
		fun = [=](Ref* ref) {DestroyOneCertainHotel(standing); };
		break;
	case 7:
		txt = "被人诬陷，进入监狱";
		fun = [=](Ref* ref) {SendToJail(standing); };
		break;
	case 8:
		txt = "被恶犬咬伤，送入医院";
		fun = [=](Ref* ref) {SendToHospital(standing); };
		break;
	case 9:
		txt = "股市增长受挫，整体表现低靡";
		fun = [=](Ref* ref) {StockMarketDown(); };
		break;
	case 10:
		txt = "政府征收所得税：";
		for (auto character : GetGameController()->getCharacters())
		{
			auto money = LevyIncomeTax(character);
			txt += StringUtils::format("\n%s:%d", character->getPlayerName().c_str(), money);
		}
		fun = [=](Ref* ref) {
			for (auto character : GetGameController()->getCharacters())
			{
				auto money = LevyIncomeTax(character);
				character->setMoney(character->getMoney() - money);
			}
			 };
		break;
	case 11:
		txt = "政府征收地产税：";
		for (auto character : GetGameController()->getCharacters())
		{
			auto money = LevyEstateTax(character);
			txt += StringUtils::format("\n%s:%d", character->getPlayerName().c_str(), money);
		}
		fun = [=](Ref* ref) {
			for (auto character : GetGameController()->getCharacters())
			{
				auto money = LevyEstateTax(character);
				character->setMoney(character->getMoney() - money);
			}
		};
		break;
	case 12:
		txt = "政府征收股票税：";
		for (auto character : GetGameController()->getCharacters())
		{
			auto money = LevyStockTax(character);
			txt += StringUtils::format("\n%s:%d", character->getPlayerName().c_str(), money);
		}
		fun = [=](Ref* ref) {
			for (auto character : GetGameController()->getCharacters())
			{
				auto money = LevyStockTax(character);
				character->setMoney(character->getMoney() - money);
			}
		};
		break;
	case 13:
		txt = StringUtils::format("闯红灯罚款%d", traffic_fine);
		fun = [=](Ref* ref) {TraficFine(standing); };
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