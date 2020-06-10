#include "Item.h"
#include "Missile.h"
#include "Character/Character.h"
#include "Common/CommonMethod.h"
#include "Incident/Staff.h"
#include "Scene/MapScene.h"
#include "Scene/ItemScene.h"

bool Missile::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "导弹";
	content_ = "向地图上指定的一个路径上的有效位置发射导弹，在3*3的区域内造成人员损伤和房屋被摧毁，允许拖拽空地移动地图";
	return true;
}

void Missile::work(Character* character)
{
	auto label = Label::createWithSystemFont(ZH("请选择"), "fonts/arial.ttf", 40);
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto map_scene = GetMapScene();
	label->setPosition(visible_size.height/2,visible_size.height*(7.f/8.f));
	map_scene->addChild(label);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		log("callback");
		int index=map_scene->touchIndex(touch->getLocation());
		if (index == -1) return false;
		log("on road");
		//先来点动画啥的不？
		LaunchMissile(index);
		label->removeFromParentAndCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, map_scene);
	return;
}