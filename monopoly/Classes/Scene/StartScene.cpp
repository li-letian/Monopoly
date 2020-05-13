#include "Scene/StartScene.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	return StartScene::create();
}


bool StartScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MenuItemFont::setFontName("ºÚÌå");
	MenuItemFont::setFontSize(20);

	auto select_item = MenuItemFont::create("Start Game", [&](Ref* render)
	{
		Director::getInstance()->end();
	});
	auto setting_item = MenuItemFont::create("Setting", [&](Ref* render)
	{
		Director::getInstance()->end();
	});
	auto close_item = MenuItemFont::create("Close", [&](Ref* render)
	{
		Director::getInstance()->end();
	});

	float x = origin.x + visibleSize.width/7;
	float y = origin.y + visibleSize.width /5;
	setting_item->setPosition(Vec2(x, y));
	
	x = origin.x + visibleSize.width / 2;
	y = origin.y + visibleSize.width / 5;
	select_item->setPosition(Vec2(x, y));

	x = origin.x + visibleSize.width * 6 / 7;
	y = origin.y + visibleSize.width / 5;
	close_item->setPosition(Vec2(x, y));

	Vector<MenuItem*> menus;
	menus.pushBack(setting_item);
	menus.pushBack(select_item);
	menus.pushBack(close_item);
	auto menu = Menu::createWithArray(menus);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto label = Label::createWithTTF("Monopoly", "fonts/Marker Felt.ttf", 50);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + 4*visibleSize.height/5 - label->getContentSize().height));
	this->addChild(label, 1);
	return true;
}