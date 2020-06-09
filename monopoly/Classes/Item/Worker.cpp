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
	name_ = "��������";
	content_ = "���ڵ�ͼ��ָ����һ����Чλ�ò��û������ˣ����˵����ڶ��֣��򽵼����������Լ�����������ֻ���ù��õ���Ч�����϶��յ��ƶ���ͼ";
	return true;
}

void Worker::work(Character* character)
{
	auto label = Label::createWithSystemFont(ZH("��ѡ��"), "fonts/arial.ttf", 40);
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto map_scene = GetMapScene();
	label->setPosition(visible_size.height / 2, visible_size.height * (7.f / 8.f));
	map_scene->addChild(label);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{

		int index = map_scene->touchIndex(touch->getLocation());
		if (index ==-1 ) return false;
		//�����㶯��ɶ�Ĳ���
		UseRobotWorker(character, index);
		label->removeFromParentAndCleanup(true);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, map_scene);
	return;
}