#include "Scene/SelectScene.h"
#include "Scene/StartScene.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"

USING_NS_CC;

Scene* SelectScene::createScene()
{
	return SelectScene::create();
}


bool SelectScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	/* 这里等后面添背景
	auto background = Sprite::create("startbackground.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(origin);
	this->addChild(background, 0);*/
	

	MenuItemFont::setFontName("华文琥珀");
	MenuItemFont::setFontSize(20);

	auto exit_item = MenuItemFont::create("Exit", [&](Ref* render)
	{
		auto scene = StartScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f,scene,Color3B(0,255,255)));
	});
	auto start_item = MenuItemFont::create("Start", [&](Ref* render)
	{
			GameController::create();
	});

	float x = origin.x + visibleSize.width / 7;
	float y = origin.y + visibleSize.width / 5;
	start_item->setPosition(Vec2(x, y));

	x = origin.x + visibleSize.width * 6 / 7;
	y = origin.y + visibleSize.width / 5;
	exit_item->setPosition(Vec2(x, y));

	Vector<MenuItem*> menus;
	menus.pushBack(start_item);
	menus.pushBack(exit_item);
	auto menu = Menu::createWithArray(menus);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}