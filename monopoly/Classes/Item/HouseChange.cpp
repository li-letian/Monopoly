#include "HouseChange.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Common/CommonConstant.h"
#include "Land/Land.h"
#include "Land/Business.h"

void HouseChange::work(Character* player) {

	auto label = Label::createWithSystemFont(ZH("请选择"), "fonts/arial.ttf", 40);
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto map_scene = GetMapScene();
	label->setPosition(visible_size.height / 2, visible_size.height * (7.f / 8.f));
	map_scene->addChild(label);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		int index = map_scene->touchIndex(touch->getLocation());
		if (index == -1) return false;
		if (map_scene->getType(index) != land_business) return false;
		auto land = dynamic_cast<Business*>(map_scene->getLand(index));
		if (!land) return false;
		if (!land->getOwner()) return false;

		land->demote();
		land->promote(true);

		label->removeFromParentAndCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, map_scene);

}

bool HouseChange::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "改建证明";
	content_ = "更改一个选定商业建筑的类型";
	return true;
}