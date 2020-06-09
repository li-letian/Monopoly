#include "cocos2d.h"
#include "Land.h"
#include "Business.h"
#include "Scene/MapScene.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Incident/Holiday.h"

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
		initWithFile("park.png");
		setAnchorPoint(Vec2(0.5f, 0.0f));
		setPosition(x, y);
		SendMsg(msg_make_go_apper);
		});
	pic.push_back("resort.png");
	callback.push_back([=](Ref* ref) {
		type_ = land_resort;
		initWithFile("resort.png");
		setAnchorPoint(Vec2(0.5f, 0.0f));
		setPosition(x, y);
		SendMsg(msg_make_go_apper);
		});
	pic.push_back("mall.png");
	callback.push_back([=](Ref* ref) {
		type_ = land_mall;
		initWithFile("mall.png");
		setAnchorPoint(Vec2(0.5f, 0.0f));
		setPosition(x, y);
		SendMsg(msg_make_go_apper);
		});
	pic.push_back("institute.png");
	callback.push_back([=](Ref* ref) {
		type_ = land_institute;
		initWithFile("institute.png");
		setAnchorPoint(Vec2(0.5f, 0.0f));
		setPosition(x, y);
		onBusinessLand(owner_);
		});
	pop->setMenu(pic, callback);
	pop->setCallBack([=](Ref* ref) {SendMsg(msg_make_go_apper); }, "ȡ��");
	pop->setPosition(Vec2(0, 0));
	map_scene->addChild(pop, 51);
	return true;
}

bool Business::demote()
{
	if (type_!=4) type_=4;
	init();
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
			std::vector<std::string>pic;
			std::vector<ccMenuCallback>callback;
			pic.push_back("mall.png");
			callback.push_back([=](Ref* ref) {
				SendMsg(msg_make_go_apper);
			});
			pop->setMenu(pic, callback);
			pop->setPosition(Vec2(0, 0));
			map_scene->addChild(pop, 51);
		}
		else
		{
			SendMsg(msg_make_go_apper);
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
					SendMsg(msg_make_go_apper);
				}
				else
				{
					//����Ū�Ʋ�
					SendMsg(msg_make_go_apper);
				}
			};
			pop->setCallBack(yes);
			pop->setPosition(Vec2(0, 0));
			map_scene->addChild(pop, 50);
		}
		else if (type_ == land_mall)
		{
			auto rent_value=rent_value_ * 5;
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
					SendMsg(msg_make_go_apper);
				}
				else
				{
					//����Ū�Ʋ�
					SendMsg(msg_make_go_apper);
				}
			};
			pop->setCallBack(yes);
			pop->setPosition(Vec2(0, 0));
			map_scene->addChild(pop, 50);
		}
		else
		{
			SendMsg(msg_make_go_apper);
		}
	}
	return true;
}

bool Business::onLand(Character* standing)
{
	auto map_scene = GetMapScene();
	if (!owner_)
	{
		auto pop = PopUpLayer::create();
		pop->setTitle(name_);
		auto text = std::string("���������Ǻ���ǰ����һ����أ�ȷ���� ") + StringUtils::format("%d", sell_value_) + std::string("�ļ۸������������");
		pop->setContent(text);
		auto yes = [=](Ref* ref)
		{
			auto money = standing->getMoney();
			if (money > sell_value_)
			{
				standing->setMoney(money - sell_value_);
				owner_ = standing;
				color_ = Sprite::create(StringUtils::format("character%d.png", standing->getTag()));
				color_larger_=Sprite::create(StringUtils::format("character%d.png", standing->getTag()));
				color_larger_->setPosition(map_scene->pos(index_larger_));
				color_larger_->setAnchorPoint(Vec2(0.5f, 0.5f));
				color_->setPosition(map_scene->pos(index_));
				color_->setAnchorPoint(Vec2(0.5f, 0.5f));
				map_scene->getMap()->addChild(color_, 1);
				map_scene->getMap()->addChild(color_larger_, 1);
				SendMsg(msg_make_go_apper);
				//���㶫����ʾ�Ѿ�������
			}
			else
			{
				auto fail = PopUpLayer::create();
				fail->setTitle("����ʧ��");
				fail->setContent("Ǯ��������զ���������أ���ȥ����Ǯ��");
				fail->setCallBack([=](Ref* ref) {
					SendMsg(msg_make_go_apper); });
				fail->setPosition(Vec2(0, 0));
				map_scene->addChild(fail, 51);
			}
		};
		auto no = [=](Ref* ref) { SendMsg(msg_make_go_apper); };
		pop->setCallBack(yes, no);
		pop->setPosition(Vec2(0, 0));
		map_scene->addChild(pop, 50);
	}
	else
	{
		if (type_ == land_business&& standing->getTag() == owner_->getTag())
		{
			auto pop = PopUpLayer::create();
			pop->setTitle(name_);
			auto text = std::string("���������Ǻ���ǰ����һ����أ�ȷ��Ҫ�������������");
			pop->setContent(text);
			auto yes = [=](Ref* ref)
			{
				promote();
			};
			auto no = [=](Ref* ref) {SendMsg(msg_make_go_apper); };
			pop->setCallBack(yes, no);
			pop->setPosition(Vec2(0, 0));
			map_scene->addChild(pop, 50);
		}
		else
		{
			onBusinessLand(standing);
		}
	}
	return true;
}