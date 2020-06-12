#include "God/God.h"
#include "God/Angel.h"
#include "God/Devil.h"
#include "God/Earth.h"
#include "God/Luck.h"
#include "God/Poor.h"
#include "God/Rich.h"
#include "God/Unluck.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"

God::God(const std::string& name)
	:pos_index_(-1), name_(name)
{

}

God* God::createGod(int god_type)
{
	God* god = nullptr;
	switch (god_type)
	{
	case angel:
		god = Angel::create();
		break;
	case devil:
		god = Devil::create();
		break;
	case earth:
		god = Earth::create();
		break;
	case luck:
		god = Luck::create();
		break;
	case poor:
		god = Poor::create();
		break;
	case rich:
		god = Rich::create();
		break;
	case unluck:
		god = Unluck::create();
		break;
	}
	return god;
}

bool God::onLand(Character* standing)
{
	if (standing->getCondition() == normal)
	{
		if (standing->getGodPossessed() == no_god)
		{
			removeGodFromMap();
			addToCharacter(standing);
			popUpExplain();
			return true;
		}
		else
		{
			GetGameController()->dealWithLand();
			return true;
		}
	}
	else
	{
		return false;
	}
}

void God::initGodImage()
{
	this->initWithFile(name_ + std::string("Image.png"));
	this->setAnchorPoint(Vec2(0.5f, 0.15f));
}

bool God::setPos(int pos_index, MapScene* map_scene)
{
	//warning:千万不要在此函数中使用GetMapScene()!!!
	if (pos_index >= map_scene->totalPosition() || pos_index < 0)
	{
		return false;
	}
	else
	{
		if (map_scene->setGod(pos_index, this))
		{
			pos_index_ = pos_index;
			this->setPosition(map_scene->pos(pos_index_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

int God::getPos()const
{
	return pos_index_;
}

void God::popUpExplain(bool deal_with_land)
{
	//展示解释框
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create(name_ + std::string("Pop.png"));
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sprite->setPosition(Vec2(visible_size.height / 2, visible_size.height / 2));
	auto map_scene = GetMapScene();
	map_scene->addChild(sprite, 50);

	//刷新神灵的地图位置
	GetGameController()->updateGod(this->getTag());

	//一段时间后将解释框隐藏，之后dealWithLand
	auto popFadeCallFunc = CallFunc::create([=]() {
		sprite->removeFromParentAndCleanup(true);
		if (deal_with_land)
		{
			GetGameController()->dealWithLand();
		}
		});
	auto sequence = Sequence::create(DelayTime::create(2.0f), popFadeCallFunc, nullptr);
	map_scene->runAction(sequence);
}

void God::removeGodFromMap()
{
	if (GetMapScene()->reMoveGod(pos_index_))
	{
		this->removeFromParent();
	}
}

void God::addToCharacter(Character* standing)
{
	standing->setGodPossessed(this->getTag());
	this->pos_index_ = -1;
	if (name_ == "Earth")
	{
		standing->setGodTimes(earth_duration_time);
	}
	else
	{
		standing->setGodTimes(weak_god_duration_time);
	}
	auto width = standing->getContentSize().width;
	this->setPosition(Vec2(width / 2, 100.0f));
	this->setAnchorPoint(Vec2(0.5f, 0.15f));
	standing->addChild(this, 11, "god");
}