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
		pRet->name_ = std::string("����");
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
		txt = "��������������Ь����";
		fun = [=](Ref* ref) {DestroySpecialShoes(standing); };
		break;
	case 1:
		pos = GetRandomHotel();
		txt = StringUtils::format("%d�������ֵ������ۼ�ȫ������", pos);
		fun = [=](Ref* ref) {SellPriceRise(pos); };
		break;
	case 2:
		pos = GetRandomHotel();
		txt = StringUtils::format("%d�������ֵ����ݹ�·��ȫ���½�", pos);
		fun = [=](Ref* ref) {RentPriceDown(pos); };
		break;
	case 3:
		txt = "ɽ�廬�µ���ĳ�ط��ݱ����״ݻ�";
		fun = [=](Ref* ref) {DestroyOneRandomHouse(); };
		break;
	case 4:
		txt = "������ĳ���ַ����������ݻ�";
		fun = [=](Ref* ref) {DestroyOneRandomStreetHouse(); };
		break;
	case 5:
		txt = "UFO���٣����ĳ�����ݴݻ�";
		fun = [=](Ref* ref) {DestroyOneCertainHouse(standing); };
		break;
	case 6:
		txt = "��������������һƬ����";
		fun = [=](Ref* ref) {DestroyOneCertainHotel(standing); };
		break;
	case 7:
		txt = "�������ݣ��������";
		fun = [=](Ref* ref) {SendToJail(standing); };
		break;
	case 8:
		txt = "����Ȯҧ�ˣ�����ҽԺ";
		fun = [=](Ref* ref) {SendToHospital(standing); };
		break;
	case 9:
		txt = "���������ܴ죬������ֵ���";
		fun = [=](Ref* ref) {StockMarketDown(); };
		break;
	case 10:
		txt = "������������˰��";
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
		txt = "�������յز�˰��";
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
		txt = "�������չ�Ʊ˰��";
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
		txt = StringUtils::format("����Ʒ���%d", traffic_fine);
		fun = [=](Ref* ref) {TraficFine(standing); };
		break;
	default:
		txt = "ƽ����һ�죬ʲô��û�з���";
		fun = [=](Ref* ref) {};
		break;
	}
	pop->setContent(txt);
	pop->setCallBack([=](Ref* ref) {fun(ref); SendMsg(msg_make_go_apper); });
	pop->setPosition(Vec2(0, 0));
	map_scene_->addChild(pop, 51);
	return true;
}