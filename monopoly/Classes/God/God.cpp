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
	this->initWithFile(StringUtils::format("%sImage.png", name_));
	this->setAnchorPoint(Vec2(0.5f, 0.15f));
}

bool God::setPos(int pos_index)
{
	auto map_scene = GetMapScene();
	if (pos_index >= map_scene->totalPosition() || pos_index < 0)
	{
		return false;
	}
	else
	{
		if (pos_index_ >= 0)
		{
			map_scene->getGod(pos_index) = nullptr;
		}
		pos_index_ = pos_index;
		if (map_scene->setGod(pos_index_, this))
		{
			this->setPosition(map_scene->pos(pos_index_));
			map_scene->getMap()->addChild(this, 10);
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

void God::popUpExplain()
{
	auto sprite = Sprite::create(StringUtils::format("%sPop.png", name_));
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	auto visible_size = Director::getInstance()->getVisibleSize();
	sprite->setPosition(Vec2(visible_size.width / 2, visible_size.height / 2));
	auto map_scene = GetMapScene();
	auto popFadeCallFunc = CallFunc::create([=]() {
		sprite->removeFromParentAndCleanup(true);
		GetGameController()->dealWithLand();
		});
	auto sequence = Sequence::create(DelayTime::create(2.0f), popFadeCallFunc, nullptr);
	map_scene->runAction(sequence);
}

bool God::setPossesed(Character* standing,int god_type)
{
	if (standing->getCondition() != normal)
	{
		return false;
	}
	else
	{
		if (standing->getGodPossessed() == no_god)
		{
			standing->setGodPossessed(god_type);
			GetMapScene()->reMoveGod(pos_index_);
			GetGameController()->updateGod(god_type);
			pos_index_ = 0;
			this->setPosition(Vec2(0, 100));
			standing->addChild(this, 12);
			popUpExplain();
		}
	}
}