#include "Bank.h"
#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonMethod.h"

#include<string>

USING_NS_CC;

Bank* Bank::create(MapScene* map_scene, int index)
{
	auto pRet = new(std::nothrow) Bank();
	if (pRet && pRet->init())
	{
		pRet->setMapScene(map_scene);
		pRet->index_ = index;
		pRet->name_ = std::string("中央银行");
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

bool Bank::onLand(Character* standing)
{
	return true;
}
bool Bank::byLand(Character* standing)
{
	return true;
}


