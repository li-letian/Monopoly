#include "cocos2d.h"
#include "Land.h"
#include "Hotel.h"
#include "Scene/MapScene.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Incident/Incident.h"

USING_NS_CC;

Hotel* Hotel::create(MapScene* map_scene, int index)
{
	auto pRet = new(std::nothrow) Hotel();
	if (pRet && pRet->init())
	{
		auto tile_size = map_scene->getMap()->getTileSize();
		pRet->setMapScene(map_scene);
		pRet->index_ = index;
		pRet->rank_ = -1;
		pRet->name_ = std::string("��ͥ�ù�") + StringUtils::format("%d", index);
		pRet->sell_value_ = hotel_land_value;
		pRet->rent_value_ = 0;
		pRet->setAnchorPoint(Vec2(0.5f, 0));
		pRet->setPosition(map_scene->pos(index) + Vec2(0, tile_size.height));
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

bool Hotel::promote()
{
	if (rank_ >= 4) return false;
	rank_++;
	sell_value_ = hotel_sell_value[rank_];
	rent_value_ = hotel_rent_value[rank_];
	if (!rank_) return true;
	this->initWithFile(StringUtils::format("hotel%d.png", rank_));
	setAnchorPoint(Vec2(0.5f, 0));
	setPosition(map_scene_->pos(index_) + Vec2(0, map_scene_->getMap()->getTileSize().height));
	return true;
}

bool Hotel::demote()
{
	if (!rank_) return false;
	rank_--;
	sell_value_ = hotel_sell_value[rank_];
	rent_value_ = hotel_rent_value[rank_];
	if (!rank_) init();
	else initWithFile(StringUtils::format("hotel%d.png", rank_));
	setAnchorPoint(Vec2(0.5f, 0));
	setPosition(map_scene_->pos(index_) + Vec2(0, map_scene_->getMap()->getTileSize().height));
	return true;
}

bool Hotel::onLand(Character* standing)
{
	if (!owner_)
	{
		auto sell_value = static_cast<int>(sell_value_ * sell_rise_);
		auto pop = PopUpLayer::create();
		pop->setTitle(name_);
		auto text = std::string("���������Ǻ���ǰ����һ����أ�ȷ���� ") + StringUtils::format("%d", sell_value) + std::string("�ļ۸������������");
		pop->setContent(text);
		auto yes = [=](Ref* ref)
		{
			auto money = standing->getMoney();
			if (money > sell_value)
			{
				standing->setMoney(money - sell_value);
				standing->setEstateValue(standing->getEstateValue() + sell_value);
				owner_ = standing;
				color_ = Sprite::create(StringUtils::format("character%d.png", standing->getTag()));
				color_->setPosition(map_scene_->pos(index_));
				color_->setAnchorPoint(Vec2(0.5f, 0.5f));
				map_scene_->getMap()->addChild(color_, 1);
				promote();
				sendMsg(msg_make_go_apper);
				//���㶫����ʾ�Ѿ�������
			}
			else
			{
				auto fail = PopUpLayer::create();
				fail->setTitle("����ʧ��");
				fail->setContent("Ǯ��������զ���������أ���ȥ����Ǯ��");
				fail->setCallBack([=](Ref* ref) {
					sendMsg(msg_make_go_apper); });
				fail->setPosition(Vec2(0, 0));
				map_scene_->addChild(fail, 51);
			}
		};
		auto no = [=](Ref* ref) { sendMsg(msg_make_go_apper); };
		pop->setCallBack(yes, no);
		pop->setPosition(Vec2(0, 0));
		map_scene_->addChild(pop, 50);
	}
	else
	{
		if (standing->getTag() == owner_->getTag())
		{
			if (rank_ < 4)
			{
				auto sell_value = static_cast<int>(sell_value_ * sell_rise_);
				auto pop = PopUpLayer::create();
				pop->setTitle(name_);
				auto text = std::string("���������Ǻ���ǰ����һ����أ�ȷ���� ") + StringUtils::format("%d", sell_value) + std::string("�ļ۸��������������");
				pop->setContent(text);
				auto yes = [=](Ref* ref)
				{
					auto money = standing->getMoney();
					if (money > sell_value)
					{
						standing->setMoney(money - sell_value);
						standing->setEstateValue(standing->getEstateValue() + sell_value);
						promote();
						sendMsg(msg_make_go_apper);
						//���㶫����ʾ�Ѿ�������
					}
					else
					{
						auto fail = PopUpLayer::create();
						fail->setTitle("����ʧ��");
						fail->setContent("Ǯ��������զ���������أ���ȥ����Ǯ��");
						fail->setCallBack([=](Ref* ref) {sendMsg(msg_make_go_apper); });
						fail->setPosition(Vec2(0, 0));
						map_scene_->addChild(fail, 51);
					}
				};
				auto no = [=](Ref* ref) {sendMsg(msg_make_go_apper); };
				pop->setCallBack(yes, no);
				pop->setPosition(Vec2(0, 0));
				map_scene_->addChild(pop, 50);
			}
			else
			{
				sendMsg(msg_make_go_apper);
			}
		}
		else
		{
			auto pop = PopUpLayer::create();
			pop->setTitle(name_);
			auto rent = rent_value_;
			for (int index = index_ + 1; map_scene_->getType(index) == land_hotel || map_scene_->getType(index) == land_business; index++)
			{
				if (map_scene_->getType(index) == land_business) continue;
				auto land = map_scene_->getLand(index);
				if (!land) continue;
				auto hotel = static_cast<Hotel*>(map_scene_->getLand(index));
				if (hotel->owner_->getTag() == owner_->getTag())
				{
					rent += hotel->rent_value_;
				}
			}
			for (int index = index_ - 1; map_scene_->getType(index) == land_hotel || map_scene_->getType(index) == land_business; index--)
			{
				if (map_scene_->getType(index) == land_business) continue;
				auto land = map_scene_->getLand(index);
				if (!land) continue;
				auto hotel = dynamic_cast<Hotel*>(map_scene_->getLand(index));
				if (hotel->owner_->getTag() == owner_->getTag())
				{
					rent += hotel->rent_value_;
				}
			}
			auto rent_value = static_cast<int>(rent * rent_rise_);
			if (owner_->getCondition() == normal)
			{
				auto text = std::string("������ ") + owner_->getPlayerName() + std::string(" ���õ�ز�������Ҫ����ס�޷� ") + StringUtils::format("%d", rent_value) + std::string("����л���Ĺ���");
				pop->setContent(text);
				auto yes = [=](Ref* ref)
				{
					auto money = standing->getMoney();
					if (money > rent_value)
					{
						standing->setMoney(money - rent_value);
						owner_->setGainValue(owner_->getGainValue() + rent_value);
						owner_->setMoney(owner_->getMoney() + rent_value);
						sendMsg(msg_make_go_apper);
					}
					else
					{
						//����Ū�Ʋ�
						sendMsg(msg_make_go_apper);
					}
				};
				pop->setCallBack(yes);
				pop->setPosition(Vec2(0, 0));
				map_scene_->addChild(pop, 50);
			}
			else
			{
				auto text = std::string("�˴������������ߵ�ǰû����ȡ���ã����ι�·���");
				pop->setContent(text);
				pop->setCallBack([=](Ref* ref) {sendMsg(msg_make_go_apper); });
				pop->setPosition(Vec2(0, 0));
				map_scene_->addChild(pop, 50);
			}
		}
	}
	return true;
}

bool Hotel::setRentRise(float rise_rate)
{
	rent_rise_ = static_cast<float>(sell_rise_ * (1 + rise_rate));
	return true;
}

bool Hotel::setSellRise(float rise_rate)
{
	sell_rise_ = static_cast<float>(sell_rise_ * (1 + rise_rate));
	return true;
}

int Hotel::getRank()const
{
	return rank_;
}

Character* Hotel::getOwner()const
{
	return owner_;
}

bool Hotel::setOwner(Character* character)
{
	if (!owner_)
	{
		character->setEstateValue(character->getEstateValue() + sell_value_ * sell_rise_);
		owner_ = character;
		color_ = Sprite::create(StringUtils::format("character%d.png", character->getTag()));
		color_->setPosition(map_scene_->pos(index_));
		color_->setAnchorPoint(Vec2(0.5f, 0.5f));
		map_scene_->getMap()->addChild(color_, 1);
		return true;
	}
	else
	{
		owner_->setEstateValue(owner_->getEstateValue() - sell_value_ * sell_rise_);
		character->setEstateValue(character->getEstateValue() + sell_value_ * sell_rise_);
		owner_ = character;
		color_->initWithFile(StringUtils::format("character%d.png", character->getTag()));
		color_->setPosition(map_scene_->pos(index_));
		color_->setAnchorPoint(Vec2(0.5f, 0.5f));
		return true;
	}
}