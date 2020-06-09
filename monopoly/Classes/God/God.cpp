#include "God/God.h"
#include "Scene/MapScene.h"
#include "Common/CommonMethod.h"

God::God(const std::string& name)
	:pos_index_(0), name_(name)
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
		pos_index_ = pos_index;
		this->setPosition(map_scene->pos(pos_index_));
		map_scene->getMap()->addChild(this, 10);
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
}