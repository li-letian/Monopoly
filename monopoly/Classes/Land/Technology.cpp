#include "Technology.h"
#include "cocos2d.h"
#include "Land.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Incident/Incident.h"

USING_NS_CC;

Technology* Technology::create( int index)
{
	auto pRet = new(std::nothrow) Technology();
	if (pRet && pRet->init())
	{
		auto map_scene = GetMapScene();
		pRet->index_ = index;
		pRet->name_ = std::string("�Ƽ���˾");
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


bool Technology::onLand(Character* standing)
{
	auto map_scene = GetMapScene();
	Character* owner = nullptr;
	auto store =GetStockScene()->getStock().at(6)->getStore();
	int total = 0;
	auto size = store.size();
	for (decltype(size) i = 0; i < size; i++)
	{
		//log("store %d :%d", i, store[i]);
		if (store[i] > total)
		{
			total = store[i];
			auto  vec = GetGameController()->getCharacters();
			for (auto c : vec)
			{
				if (c->getTag() == i)
				{
					owner = c;
				}
			}
		}
	}
	if (!owner)
	{
		if (standing->getIsAI() == false)
		{
			auto pop = PopUpLayer::create();
			pop->setTitle(name_);
			pop->setContent("��Ҫ�����³��𣿿�칺�򱾹�˾�Ĺ�ƱŶ����ǰ�ֲ��������˻��Ϊ����˾�Ķ��³������й�˾����Ȩ");
			pop->setCallBack([=](Ref* ref) { SendMsg(msg_make_go_apper); });
			pop->setPosition(Vec2(0, 0));
			map_scene->addChild(pop, 51);
		}
		else
		{
			SendMsg(msg_make_go_apper);
		}
	}
	else
	{
		if (owner == standing)
		{
			auto pop = PopUpLayer::create();
			pop->setTitle(name_);
			pop->setContent(StringUtils::format("������ %s ����", "ĳ��"));
			pop->setCallBack([=](Ref* ref)
			{
				//����һ������
				SendMsg(msg_make_go_apper);
			});
			pop->setOnScene(51);
		}
		else SendMsg(msg_make_go_apper);

	}
	return true;
}