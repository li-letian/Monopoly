#include "cocos2d.h"
#include "Land.h"
#include "Business.h"
#include "Scene/MapScene.h"
#include "Scene/ItemScene.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Incident/Holiday.h"
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

Business* Business::create(int index)
{
	auto pRet = new(std::nothrow) Business();
	if (pRet && pRet->init())
	{
		auto map_scene = GetMapScene();
		auto tile_size = map_scene->getMap()->getTileSize();
		pRet->name_ = std::string("��ҵ�õ�") + StringUtils::format("%d", index);
		pRet->setAnchorPoint(Vec2(0.5f, 0.0f));
		auto back = 0;
		for (int idx = index + 1; map_scene->getType(idx) == land_business|| map_scene->getType(idx) == land_park || map_scene->getType(idx) == land_resort || map_scene->getType(idx) == land_mall || map_scene->getType(idx) == land_institute; idx++)
		{
			back++;
		}
		if (back % 2 == 1)
		{
			pRet->index_ = index;
			pRet->index_larger_ = index + 1;
			map_scene->getLand(index + 1) = pRet;
		}
		else
		{
			pRet->index_ = index-1;
			pRet->index_larger_ = index;
			map_scene->getLand(index-1) = pRet;
		}
		auto x = 0.5f*(map_scene->pos(pRet->index_).x + map_scene->pos(pRet->index_larger_).x);
		auto y = map_scene->pos(pRet->index_).y+tile_size.height;
		pRet->setPosition(x,y);
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

bool Business::promote(bool house_change)
{
	auto map_scene = GetMapScene();
	auto tile_size = map_scene->getMap()->getTileSize();
	auto x = 0.5f * (map_scene->pos(index_).x + map_scene->pos(index_larger_).x);
	auto y = map_scene->pos(index_).y + tile_size.height;
	if (GetGameController()->getCurCharacter()->getIsAI())
	{
		type_ = land_park;
		name_ = std::string("��԰") + StringUtils::format("%d", index_);
		initWithFile("park.png");
		setAnchorPoint(Vec2(0.5f, 0.0f));
		setPosition(x, y);
		SendMsg(msg_make_go_appear);
	}
	else
	{
		auto pop = PopUpLayer::create();
		if (house_change == true)
		{
			pop->setTitle("��ѡ��Ҫ�Ľ��ĵز�");
		}
		else
		{
			pop->setTitle("��ѡ��ҪͶ�ʵĵز�");
		}
		std::vector<std::string>pic;
		std::vector<ccMenuCallback>callback;
		pic.push_back("park.png");
		callback.push_back([=](Ref* ref) {
			type_ = land_park;
			name_ = std::string("��԰") + StringUtils::format("%d", index_);
			initWithFile("park.png");
			setAnchorPoint(Vec2(0.5f, 0.0f));
			setPosition(x, y);
			SendMsg(msg_make_go_appear);
			});
		pic.push_back("resort.png");
		callback.push_back([=](Ref* ref) {
			type_ = land_resort;
			name_ = std::string("�ȼٴ�") + StringUtils::format("%d", index_);
			initWithFile("resort.png");
			setAnchorPoint(Vec2(0.5f, 0.0f));
			setPosition(x, y);
			SendMsg(msg_make_go_appear);
			});
		pic.push_back("mall.png");
		callback.push_back([=](Ref* ref) {
			type_ = land_mall;
			name_ = std::string("����㳡") + StringUtils::format("%d", index_);
			initWithFile("mall.png");
			setAnchorPoint(Vec2(0.5f, 0.0f));
			setPosition(x, y);
			SendMsg(msg_make_go_appear);
			});
		pic.push_back("institute.png");
		callback.push_back([=](Ref* ref) {
			type_ = land_institute;
			name_ = std::string("�з�����") + StringUtils::format("%d", index_);
			initWithFile("institute.png");
			setAnchorPoint(Vec2(0.5f, 0.0f));
			setPosition(x, y);
			onBusinessLand(owner_);
			});
		pop->setMenu(pic, callback);
		pop->setCallBack([=](Ref* ref) {SendMsg(msg_make_go_appear); }, "ȡ��");
		pop->setPosition(Vec2(0, 0));
		map_scene->addChild(pop, 51);
		return true;
	}
	return true;
}

bool Business::demote()
{
	if (type_!=4) type_=4;
	init();
	name_ = std::string("��ҵ�õ�") + StringUtils::format("%d", index_);
	setAnchorPoint(Vec2(0.5f, 0.0f));
	auto map_scene = GetMapScene();
	auto tile_size = map_scene->getMap()->getTileSize();
	auto x = 0.5f * (map_scene->pos(index_).x + map_scene->pos(index_larger_).x);
	auto y = map_scene->pos(index_).y + tile_size.height;
	setPosition(x, y);
	return true;
}

bool Business::onBusinessLand(Character* standing)
{
	auto map_scene = GetMapScene();
	if (standing->getTag() == owner_->getTag())
	{
		if (type_ == land_institute)
		{
			auto pop = PopUpLayer::create();
			pop->setTitle("��ѡ��Ҫ�з��ĵ���");
			std::vector<std::string>txt;
			std::vector<ccMenuCallback>callback;

			switch (random(3))
			{
			case 0:
				txt.push_back(" ��ʹ�� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, AngelCard::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ң������ ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, ControlDice::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" �Ľ�֤�� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, HouseChange::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ����� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Pray::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ��Ժ֤�� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, RidHospital::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" �ȼٿ� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Sleep::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" �ڹ����� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Turtle::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ��ͬ��ԣ ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Average::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ��ħ�� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, DevilCard::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ���޿� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, HouseDestory::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				break;
			case 1:
				txt.push_back(" ���� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Mine::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" �쿨 ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, RedCard::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ����֤�� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, RidJail::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ͣ���� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Stop::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" �������� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Worker::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" �ڿ� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, BlackCard::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ��ң���� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Escape::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ����֤�� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, HouseExchange::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ���� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Missile::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ���� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Revenge::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				break;
			default:
				txt.push_back(" �Ǽۿ� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, RisePrice::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ���ͻ� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Transmit::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ��Ь ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Car::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" �ݺ��� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Frame::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" �޻��� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Impute::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" Զ��Ь ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Motor::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ����� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, RidGod::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" �������� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, Robot::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
				txt.push_back(" ת�� ");
				callback.push_back([=](Ref* ref) {
					GetItemScene()->addItem(standing, TurnAround::create());
					pop->removeFromParentAndCleanup(true);
					SendMsg(msg_make_go_appear);
				});
			 break;
			}

			pop->setMenu(callback,txt);
			pop->setCallBack([=](Ref* ref) {},"ȡ��");
			pop->setPosition(Vec2(0, 0));
			map_scene->addChild(pop, 51);
		}
		else
		{
			SendMsg(msg_make_go_appear);
		}
	}
	if(standing->getTag() != owner_->getTag())
	{
		if (type_ == land_resort)
		{
			auto rent_value=rent_value_ * 2;
			auto pop = PopUpLayer::create();
			pop->setTitle(name_);
			pop->setContent(std::string("������ ") + owner_->getPlayerName() + std::string(" �Ķȼٴ壬����Ҫ֧�� ") + StringUtils::format("%d", rent_value) + std::string(" �� ")+StringUtils::format("%d", default_stop_times)+std::string(" ������ȼ��ײͣ���л���Ĺ���"));
			auto yes = [=](Ref* ref)
			{
				auto money = standing->getMoney();
				if (money > rent_value)
				{
					standing->setMoney(money - rent_value);
					owner_->setGainValue(owner_->getGainValue() + rent_value);
					owner_->setMoney(owner_->getMoney() + rent_value);
					GoOnHoliday(standing);
					SendMsg(msg_make_go_appear);
				}
				else
				{
					//����Ū�Ʋ�
					SendMsg(msg_make_go_appear);
				}
			};
			pop->setCallBack(yes);
			pop->setOnScene();
		}
		else if (type_ == land_mall)
		{
			auto rent_value=rent_value_ * GetItemScene()->getItemSize(standing);
			auto pop = PopUpLayer::create();
			pop->setTitle(name_);
			pop->setContent(std::string("������ ") + owner_->getPlayerName() + std::string(" �Ĺ����̳�������Ҫ֧������ѷ��� ") + StringUtils::format("%d", rent_value) + std::string("����л���Ĺ���"));
			auto yes = [=](Ref* ref)
			{
				auto money = standing->getMoney();
				if (money > rent_value)
				{
					standing->setMoney(money - rent_value);
					owner_->setGainValue(owner_->getGainValue() + rent_value);
					owner_->setMoney(owner_->getMoney() + rent_value);
					SendMsg(msg_make_go_appear);
				}
				else
				{
					//����Ū�Ʋ�
					SendMsg(msg_make_go_appear);
				}
			};
			pop->setCallBack(yes);
			pop->setOnScene();
		}
		else
		{
			SendMsg(msg_make_go_appear);
		}
	}
	return true;
}

bool Business::onLand(Character* standing)
{
	auto map_scene = GetMapScene();
	if (!owner_)
	{
		auto yes = [=](Ref* ref)
		{
			auto money = standing->getMoney();
			if (money > sell_value_)
			{
				standing->setMoney(money - sell_value_);
				owner_ = standing;
				color_ = Sprite::create(StringUtils::format("character%d.png", standing->getTag()));
				color_larger_ = Sprite::create(StringUtils::format("character%d.png", standing->getTag()));
				color_larger_->setPosition(map_scene->pos(index_larger_));
				color_larger_->setAnchorPoint(Vec2(0.5f, 0.5f));
				color_->setPosition(map_scene->pos(index_));
				color_->setAnchorPoint(Vec2(0.5f, 0.5f));
				map_scene->getMap()->addChild(color_, 1);
				map_scene->getMap()->addChild(color_larger_, 1);
				SendMsg(msg_make_go_appear);
				//���㶫����ʾ�Ѿ�������
			}
			else
			{
				auto fail = PopUpLayer::create();
				fail->setTitle("����ʧ��");
				fail->setContent("Ǯ��������զ���������أ���ȥ����Ǯ��");
				fail->setCallBack([=](Ref* ref) {
					SendMsg(msg_make_go_appear); });
				fail->setPosition(Vec2(0, 0));
				map_scene->addChild(fail, 51);
			}
		};
		auto no = [=](Ref* ref) { SendMsg(msg_make_go_appear); };
		//�����AI
		if (standing->getIsAI())
		{
			switch (random(2))
			{
			case AI_yes:
				if (standing->aiFinanceOK(sell_value_))
				{
					yes(nullptr);
				}
				else
				{
					no(nullptr);
				}
				break;
			case AI_no:
				no(nullptr);
			}
		}
		else
		{
			auto pop = PopUpLayer::create();
			pop->setTitle(name_);
			auto text = std::string("���������Ǻ���ǰ����һ����أ�ȷ���� ") + StringUtils::format("%d", sell_value_) + std::string("�ļ۸������������");
			pop->setContent(text);
			pop->setCallBack(yes, no);
			pop->setPosition(Vec2(0, 0));
			map_scene->addChild(pop, 50);
		}
	}
	else
	{
		if (type_ == land_business&& standing->getTag() == owner_->getTag())
		{
			auto yes = [=](Ref* ref)
			{
				promote();
			};
			auto no = [=](Ref* ref) {SendMsg(msg_make_go_appear); };
			if (standing->getIsAI())
			{
				switch (random(2))
				{
				case AI_yes:
					yes(nullptr);
					break;
				case AI_no:
					no(nullptr);
					break;
				}
			}
			else
			{
				auto pop = PopUpLayer::create();
				pop->setTitle(name_);
				auto text = std::string("���������Ǻ���ǰ����һ����أ�ȷ��Ҫ�������������");
				pop->setContent(text);
				pop->setCallBack(yes, no);
				pop->setPosition(Vec2(0, 0));
				map_scene->addChild(pop, 50);
			}
		}
		else
		{
			onBusinessLand(standing);
		}
	}
	return true;
}