#include "Mine.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Scene/GameController.h"

void Mine::work(Character* player) {
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
		auto characters = GetGameController()->getCharacters();
		for (auto c : characters)
		{
			if (c->getCurPos() == index)
				return false;
		}
		SetMinePosition(index);
		label->removeFromParentAndCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, map_scene);
	

}

bool Mine::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "地雷";
	content_ = "请选择一个没有人和神的有效地点，放置地雷，可拖动空地改变视角";
	return true;
}