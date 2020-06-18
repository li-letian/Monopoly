#include "Land/Hospital.h"
#include "cocos2d.h"
#include "Land.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Incident/Incident.h"
#include "Scene/ItemScene.h"
#include "Item/Item.h"

USING_NS_CC;

Hospital* Hospital::create( int index)
{
	auto pRet = new(std::nothrow) Hospital();
	if (pRet && pRet->init())
	{
		auto map_scene = GetMapScene();
		auto tile_size = map_scene->getMap()->getTileSize();
		pRet->index_ = index;
		pRet->name_ = std::string("ҽԺ");
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


bool Hospital::onLand(Character* standing)
{
	if (standing->getIsAI())
	{
		SendMsg(msg_make_go_apper);
		return false;
	}
	//Ҫ��û�г�Ժ֤����ֱ���˳�
	auto item = GetItemScene()->getItem(standing, "��Ժ֤��");
	if (item == nullptr) return false;
	auto map_scene = GetMapScene();
	auto tile_size = map_scene->getMap()->getTileSize();
	auto& characters = dynamic_cast<GameController*>(Director::getInstance()->getRunningScene()->getChildByName("game_controller"))->getCharacters();
	auto pop = PopUpLayer::create();
	pop->setTitle("��ѡ��Ҫ�����Ժ����");
	std::vector<std::string>pic;
	std::vector<ccMenuCallback>callback;

	for (auto character : characters)
	{
		if (character->getCondition() == in_hospital)
		{
			pic.push_back(character->getPlayerName() + std::string("_avatar.png"));
			callback.push_back([=](Ref* ref) {
				character->setStopTimes(0);
				PopUpHospitalDialog(character);
				GetItemScene()->removeItem(standing, item);
			});
		}
	}
	pop->setMenu(pic, callback);
	pop->setCallBack([=](Ref* ref) {SendMsg(msg_make_go_apper); }, "ȡ��");
	pop->setPosition(Vec2(0, 0));
	map_scene->addChild(pop, 51);
	return true;
}