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
	name_ = "����";
	content_ = "���ͼ��ָ����һ��·���ϵ���Чλ�÷��䵼������3*3�������������Ա���˺ͷ��ݱ��ݻ٣�������ק�յ��ƶ���ͼ";
	return true;
}

void Missile::work(Character* character)
{
	auto label = Label::createWithSystemFont(ZH("��ѡ��"), "fonts/arial.ttf", 40);
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
		//�����㶯��ɶ�Ĳ���
		LaunchMissile(index);
		label->removeFromParentAndCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, map_scene);
	return;
}