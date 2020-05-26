#include "GameController.h"
#include "MapScene.h"

bool GameController::init()
{
	auto scene = MapScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B(0, 255, 255)));
	return true;
}

