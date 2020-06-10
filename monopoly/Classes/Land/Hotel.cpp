#include "cocos2d.h"
#include "Land.h"
#include "Hotel.h"
#include "Scene/MapScene.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Incident/Incident.h"
#include "God/Angel.h"
#include "God/Devil.h"
#include "God/Earth.h"
#include "God/Luck.h"
#include "God/Poor.h"
#include "God/Rich.h"
#include "God/Unluck.h"

USING_NS_CC;

Hotel* Hotel::create(int index)
{
	auto pRet = new(std::nothrow) Hotel();
	if (pRet && pRet->init())
	{
		auto map_scene = GetMapScene();
		auto tile_size = map_scene->getMap()->getTileSize();
		pRet->index_ = index;
		pRet->rank_ = -1;
		pRet->name_ = std::string("家庭旅馆") + StringUtils::format("%d", index);
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
	auto map_scene = GetMapScene();
	rank_++;
	sell_value_ = hotel_sell_value[rank_];
	rent_value_ = hotel_rent_value[rank_];
	if (!rank_) return true;
	this->initWithFile(StringUtils::format("hotel%d.png", rank_));
	setAnchorPoint(Vec2(0.5f, 0));
	setPosition(map_scene->pos(index_) + Vec2(0, map_scene->getMap()->getTileSize().height));
	return true;
}

bool Hotel::demote()
{
	if (rank_ <= 0) return false;
	rank_--;
	auto map_scene = GetMapScene();
	sell_value_ = hotel_sell_value[rank_];
	rent_value_ = hotel_rent_value[rank_];
	if (!rank_) init();
	else initWithFile(StringUtils::format("hotel%d.png", rank_));
	setAnchorPoint(Vec2(0.5f, 0));
	setPosition(map_scene->pos(index_) + Vec2(0, map_scene->getMap()->getTileSize().height));
	return true;
}

bool Hotel::onLand(Character* standing)
{
	auto map_scene = GetMapScene();
	if (!owner_)
	{
		auto sell_value = static_cast<int>(sell_value_ * sell_rise_);
		auto pop = PopUpLayer::create();
		pop->setTitle(name_);
		auto text = std::string("看起来真是很有前景的一块地呢，确认以 ") + StringUtils::format("%d", sell_value) + std::string("的价格购买这块土地吗？");
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
				color_->setPosition(map_scene->pos(index_));
				color_->setAnchorPoint(Vec2(0.5f, 0.5f));
				map_scene->getMap()->addChild(color_, 1);
				promote();
				godExecute(standing, true);
				//画点东西表示已经买完了
			}
			else
			{
				auto fail = PopUpLayer::create();
				fail->setTitle("购买失败");
				fail->setContent("钱都不够了咋还还剁手呢？快去整点钱吧");
				fail->setCallBack([=](Ref* ref) {
					godExecute(standing); });
				fail->setPosition(Vec2(0, 0));
				map_scene->addChild(fail, 51);
			}
		};
		auto no = [=](Ref* ref) { godExecute(standing); };
		pop->setCallBack(yes, no);
		pop->setPosition(Vec2(0, 0));
		map_scene->addChild(pop, 50);
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
				auto text = std::string("看起来真是很有前景的一块地呢，确认以 ") + StringUtils::format("%d", sell_value) + std::string("的价格升级这块土地吗？");
				pop->setContent(text);
				auto yes = [=](Ref* ref)
				{
					auto money = standing->getMoney();
					if (money > sell_value)
					{
						standing->setMoney(money - sell_value);
						standing->setEstateValue(standing->getEstateValue() + sell_value);
						promote();
						godExecute(standing, true);
						//画点东西表示已经买完了
					}
					else
					{
						auto fail = PopUpLayer::create();
						fail->setTitle("购买失败");
						fail->setContent("钱都不够了咋还还剁手呢？快去整点钱吧");
						fail->setCallBack([=](Ref* ref) {SendMsg(msg_make_go_apper); });
						fail->setPosition(Vec2(0, 0));
						map_scene->addChild(fail, 51);
					}
				};
				auto no = [=](Ref* ref) {godExecute(standing); };
				pop->setCallBack(yes, no);
				pop->setPosition(Vec2(0, 0));
				map_scene->addChild(pop, 50);
			}
			else
			{
				SendMsg(msg_make_go_apper);
			}
		}
		else
		{
			auto pop = PopUpLayer::create();
			pop->setTitle(name_);
			auto rent = rent_value_;
			for (int index = index_ + 1; map_scene->getType(index) == land_hotel || map_scene->getType(index) == land_business; index++)
			{
				if (map_scene->getType(index) == land_business) continue;
				auto land = map_scene->getLand(index);
				if (!land) continue;
				auto hotel = static_cast<Hotel*>(map_scene->getLand(index));
				if (hotel->owner_->getTag() == owner_->getTag())
				{
					rent += hotel->rent_value_;
				}
			}
			for (int index = index_ - 1; map_scene->getType(index) == land_hotel || map_scene->getType(index) == land_business; index--)
			{
				if (map_scene->getType(index) == land_business) continue;
				auto land = map_scene->getLand(index);
				if (!land) continue;
				auto hotel = dynamic_cast<Hotel*>(map_scene->getLand(index));
				if (hotel->owner_->getTag() == owner_->getTag())
				{
					rent += hotel->rent_value_;
				}
			}
			auto rent_value = static_cast<int>(rent * rent_rise_);
			if (owner_->getCondition() == normal)
			{
				auto text = std::string("这里是 ") + owner_->getPlayerName() + std::string(" 的旅店地产，你需要缴纳住宿费 ") + StringUtils::format("%d", rent_value) + std::string("，感谢您的光临");
				pop->setContent(text);
				auto yes = [=](Ref* ref)
				{
					auto money = standing->getMoney();
					if (money > rent_value)
					{
						standing->setMoney(money - rent_value);
						owner_->setGainValue(owner_->getGainValue() + rent_value);
						owner_->setMoney(owner_->getMoney() + rent_value);
						godExecute(standing, false, rent_value);
					}
					else
					{
						//这里弄破产
						godExecute(standing);
					}
				};
				pop->setCallBack(yes);
				pop->setPosition(Vec2(0, 0));
				map_scene->addChild(pop, 50);
			}
			else
			{
				auto text = std::string("此处房产的所有者当前没空收取费用，本次过路免费");
				pop->setContent(text);
				pop->setCallBack([=](Ref* ref) {godExecute(standing); });
				pop->setPosition(Vec2(0, 0));
				map_scene->addChild(pop, 50);
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

float Hotel::getRentRise()const
{
	return rent_rise_;
}

bool Hotel::setSellRise(float rise_rate)
{
	sell_rise_ = static_cast<float>(sell_rise_ * (1 + rise_rate));
	return true;
}

float Hotel::getSellRise()const
{
	return sell_rise_;
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
	auto map_scene = GetMapScene();
	if (!owner_)
	{
		character->setEstateValue(character->getEstateValue() + static_cast<int>(sell_value_ * sell_rise_));
		owner_ = character;
		color_ = Sprite::create(StringUtils::format("character%d.png", character->getTag()));
		color_->setPosition(map_scene->pos(index_));
		color_->setAnchorPoint(Vec2(0.5f, 0.5f));
		map_scene->getMap()->addChild(color_, 1);
		return true;
	}
	else
	{
		if (character)
		{
			owner_->setEstateValue(owner_->getEstateValue() - static_cast<int>(sell_value_ * sell_rise_));
			character->setEstateValue(character->getEstateValue() + static_cast<int>(sell_value_ * sell_rise_));
			owner_ = character;
			color_->initWithFile(StringUtils::format("character%d.png", character->getTag()));
			color_->setPosition(map_scene->pos(index_));
			color_->setAnchorPoint(Vec2(0.5f, 0.5f));
			return true;
		}
		else
		{
			owner_->setEstateValue(owner_->getEstateValue() - static_cast<int>(sell_value_ * sell_rise_));
			owner_ = character;
			color_->removeFromParent();
			return true;
		}
	}
}

int Hotel::getValue()const
{
	int value = 0;
	for (int i = 0; i <= rank_; i++)
	{
		value += hotel_sell_value[i];
	}
	value = static_cast<int>(value * sell_rise_);
	return value;
}

void Hotel::godExecute(Character* standing,bool do_promote,int rent_value)
{
	switch (standing->getGodPossessed())
	{
	case no_god:
		SendMsg(msg_make_go_apper);
		break;
	case angel:
		if (rank_ >= 0 && rank_ < 4)
		{
			auto pre_value = this->getValue();
			promote();
			auto cur_value = this->getValue();
			owner_->setEstateValue(owner_->getEstateValue() + cur_value - pre_value);
			Angel::popUpDialog();
		}
		else
		{
			SendMsg(msg_make_go_apper);
		}
		break;
	case devil:
		if (rank_ >= 1)
		{
			auto pre_value = this->getValue();
			demote();
			auto cur_value = this->getValue();
			owner_->setEstateValue(owner_->getEstateValue() + cur_value - pre_value);
			Devil::popUpDialog();
		}
		else
		{
			SendMsg(msg_make_go_apper);
		}
		break;
	case earth:
		if (owner_ != standing)
		{
			this->setOwner(standing);
			Earth::popUpDialog();
		}
		else
		{
			SendMsg(msg_make_go_apper);
		}
		break;
	case luck:
		if (rank_ >= 0 && rank_ < 4 && owner_ == standing)
		{
			auto pre_value = this->getValue();
			this->promote();
			auto cur_value = this->getValue();
			owner_->setEstateValue(owner_->getEstateValue() + cur_value - pre_value);
			Luck::popUpDialog();
		}
		else
		{
			SendMsg(msg_make_go_apper);
		}
		break;
	case poor:
		if (rent_value > 0)
		{
			standing->setMoney(standing->getMoney() - rent_value);
			owner_->setGainValue(owner_->getGainValue() + rent_value);
			owner_->setMoney(owner_->getMoney() + rent_value);
		}
		else
		{
			SendMsg(msg_make_go_apper);
		}
		break;
	case rich:
		if (rent_value > 0)
		{
			standing->setMoney(standing->getMoney() + rent_value);
			owner_->setGainValue(owner_->getGainValue() - rent_value);
			owner_->setMoney(owner_->getMoney() - rent_value);
		}
		else
		{
			SendMsg(msg_make_go_apper);
		}
		break;
	case unluck:
		if (do_promote == true)
		{
			if (rank_ == 0)
			{
				setOwner(nullptr);
			}
			else
			{
				auto pre_value = this->getValue();
				demote();
				auto cur_value = this->getValue();
				owner_->setEstateValue(owner_->getEstateValue() + cur_value - pre_value);
			}
			Unluck::popUpDialog();
		}
		else
		{
			SendMsg(msg_make_go_apper);
		}
		break;
	}	
}