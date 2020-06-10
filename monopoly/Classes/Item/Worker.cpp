#include "Item.h"
#include "Worker.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Common/CommonConstant.h"
#include "Land/Hotel.h"

bool Worker::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "机器工人";
	content_ = "向在地图上指定的一个有效位置布置机器工人，若此地属于对手，则降级，若属于自己，则升级，只对旅馆用地有效，可拖动空地移动地图";
	return true;
}

void Worker::work(Character* character)
{
	auto label = Label::createWithSystemFont(ZH("请选择"), "fonts/arial.ttf", 40);
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto map_scene = GetMapScene();
	label->setPosition(visible_size.height / 2, visible_size.height * (7.f / 8.f));
	map_scene->addChild(label);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{

		int index = map_scene->touchIndex(touch->getLocation());
		if (index ==-1 ) return false;
		//先来点动画啥的不？
		UseRobotWorker(character, index);
		label->removeFromParentAndCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, map_scene);
	return;
}