#include "God/God.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"

God::God(const std::string& name)
	:pos_index_(-1), name_(name)
{

}

void God::initGodImage()
{
	this->initWithFile(name_ + std::string("Image.png"));
	this->setAnchorPoint(Vec2(0.5f, 0.15f));
}

bool God::setPos(int pos_index, MapScene* map_scene)
{
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

void God::popUpExplain(const std::string& name,int god_type)
{
	auto sprite = Sprite::create(name + std::string("Pop.png"));
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	auto visible_size = Director::getInstance()->getVisibleSize();
	sprite->setPosition(Vec2(visible_size.height / 2, visible_size.height / 2));
	auto map_scene = GetMapScene();
	map_scene->addChild(sprite, 50);
	GetGameController()->updateGod(god_type);
	auto popFadeCallFunc = CallFunc::create([=]() {
		sprite->removeFromParentAndCleanup(true);
		GetGameController()->dealWithLand();
		});
	auto sequence = Sequence::create(DelayTime::create(2.0f), popFadeCallFunc, nullptr);
	map_scene->runAction(sequence);
}

bool God::removeGodFromMap(Character* standing)
{
	if (standing->getCondition() != normal)
	{
		return false;
	}
	else
	{
		if (standing->getGodPossessed() == no_god)
		{
			GetMapScene()->reMoveGod(pos_index_);
			this->removeFromParent();
			return true;
		}
		else
		{
			return false;
		}
	}
}

void God::addToCharacter(God*god,Character* standing)
{
	if (god->name_ == "Earth")
	{
		standing->setGodTimes(earth_duration_time);
	}
	else
	{
		standing->setGodTimes(weak_god_duration_time);
	}
	auto width = standing->getContentSize().width;
	god->setPosition(Vec2(width / 2, 100.0f));
	god->setAnchorPoint(Vec2(0.5f, 0.15f));
	standing->addChild(god, 11, "god");
}