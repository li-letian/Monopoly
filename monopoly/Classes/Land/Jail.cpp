#include "Jail.h"
#include "cocos2d.h"
#include "Land.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Incident/Incident.h"

USING_NS_CC;

Jail* Jail::create(MapScene* map_scene, int index)
{
	auto pRet = new(std::nothrow) Jail();
	if (pRet && pRet->init())
	{
		auto tile_size = map_scene->getMap()->getTileSize();
		pRet->setMapScene(map_scene);
		pRet->index_ = index;
		pRet->name_ = std::string("监狱");
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


bool Jail::onLand(Character* standing)
{
	//要是没有保释证明就直接退出
	if (false) return false;
	auto tile_size = map_scene_->getMap()->getTileSize();
	auto& characters = dynamic_cast<GameController*>(Director::getInstance()->getRunningScene()->getChildByName("game_controller"))->getCharacters();
	auto pop = PopUpLayer::create();
	pop->setTitle("请选择要保释的人");
	std::vector<std::string>pic;
	std::vector<ccMenuCallback>callback;

	for (auto character : characters)
	{
		if (character->getCondition() == in_jail)
		{
			pic.push_back(character->getPlayerName() + string("_avatar.png"));
			callback.push_back([=](Ref* ref) {
				character->setStopTimes(0);
				PopUpJailDialog(character, map_scene_);
				SendMsg(msg_make_go_apper);
			});
		}
	}
	pop->setMenu(pic, callback);
	pop->setCallBack([=](Ref* ref) {SendMsg(msg_make_go_apper); }, "取消");
	pop->setPosition(Vec2(0, 0));
	map_scene_->addChild(pop, 51);
	return true;
}