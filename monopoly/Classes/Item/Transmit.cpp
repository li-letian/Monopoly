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
	name_ = "��ʱ�մ�����";
	content_ = "�ڵ�ͼ��ָ��һ����Ч���󣬿���Ϊ������߽�ɫ��Ȼ�󴫶����������߽�ɫ��ָ������һ��Чλ�ã����϶��յ�ѡȡ�ص�";
	return true;
}

void Transmit::work(Character* character)
{
	auto label = Label::createWithSystemFont(ZH("��ѡ�����"), "fonts/arial.ttf", 40);
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto map_scene = GetMapScene();
	label->setPosition(visible_size.height / 2, visible_size.height * (7.f / 8.f));
	map_scene->addChild(label);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		int index = map_scene->touchIndex(touch->getLocation());
		if (index == -1) return false;
		
		//��������Щ��ϵ��ɶ
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

void Transmit::workOnGod()
{
	auto label = Label::createWithSystemFont(ZH("��ѡ��λ��"), "fonts/arial.ttf", 40);
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto map_scene = GetMapScene();
	label->setPosition(visible_size.height / 2, visible_size.height * (7.f / 8.f));
	map_scene->addChild(label);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		int index = map_scene->touchIndex(touch->getLocation());
		if (index == -1) return false;
		

		//����Ķ���
		label->removeFromParentAndCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, map_scene);
	return;
}

void Transmit::workOnCharacter(Character * user,Character *character)
{
	auto label = Label::createWithSystemFont(ZH("��ѡ��λ��"), "fonts/arial.ttf", 40);
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