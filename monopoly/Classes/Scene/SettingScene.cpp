#include "Scene/StartScene.h"
#include "Scene/SettingScene.h"

USING_NS_CC;

Scene *SettingScene::createScene()
{
	return SettingScene::create();
}

bool SettingScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//auto background = Sprite::create("startbackground.png");
	//background->setAnchorPoint(Vec2(0, 0));
	//background->setPosition(origin);
	//this->addChild(background, 0);

	MenuItemFont::setFontName("fonts/STHUPO.ttf");
	MenuItemFont::setFontSize(20);

	auto close_item = MenuItemFont::create("Close", [&](Ref *render) {
		Director::getInstance()->popScene();
	});

	float x = origin.x + visibleSize.width * 6 / 7;
	float y = origin.y + visibleSize.width / 5;
	close_item->setPosition(Vec2(x, y));

	Vector<MenuItem *> menus;
	menus.pushBack(close_item);
	auto menu = Menu::createWithArray(menus);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}