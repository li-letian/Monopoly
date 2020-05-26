#include "Scene/GameController.h"
#include "Scene/MapScene.h"
#include "Common/CommonConstant.h"

GameController::GameController()
	:map_scene_(NULL)
{

}

bool GameController::init()
{
	//创造map_scene场景并切换
	map_scene_ = MapScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, map_scene_, Color3B(0, 255, 255)));
	
	addCharacter("miku", miku, 15000, map_scene_->pos_.at(0));
	addCharacter("nanxiaoniao", nanxiaoniao, 15000, map_scene_->pos_.at(1));
	return true;
}

void GameController::addCharacter(const std::string&name,int tag,int money,Vec2 start_pos)
{
	auto character = Character::create(name, tag, money);
	character->setPosition(start_pos);
	map_scene_->map_->addChild(character,10);
}
