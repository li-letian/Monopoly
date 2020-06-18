#include "Item.h"
#include "Transmit.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"
#include "Land/Hotel.h"
#include "Scene/GameController.h"

bool Transmit::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "传送仪";
	content_ = "在地图上指定一个角色，然后传动这个角色到指定的另一有效位置，可拖动空地选取地点";
	return true;
}

void Transmit::work(Character* character)
{
	auto label = Label::createWithSystemFont(ZH("请选择对象"), "fonts/arial.ttf", 40);
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
			if (index == c->getCurPos())
			{
				workOnCharacter(character,c);
				label->removeFromParentAndCleanup(true);
				Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
				return true;
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, map_scene);
	return;
}


void Transmit::workOnCharacter(Character * user,Character *character)
{
	auto label = Label::createWithSystemFont(ZH("请选择位置"), "fonts/arial.ttf", 40);
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto map_scene = GetMapScene();
	label->setPosition(visible_size.height / 2, visible_size.height * (7.f / 8.f));
	map_scene->addChild(label);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		int index = map_scene->touchIndex(touch->getLocation());
		if (index == -1) return false;
		TransmitCharacter(user, character, index);
		label->removeFromParentAndCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, map_scene);
	return;
}