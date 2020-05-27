#include "Scene/StartScene.h"
#include "Scene/SelectScene.h"
#include "Scene/SettingScene.h"
#include "ZH.h"

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
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("startbackground.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(origin);
	this->addChild(background, 0);

	MenuItemFont::setFontName("华文琥珀");
	MenuItemFont::setFontSize(40);

	auto select_item = MenuItemFont::create(ZH("| 开始游戏 |"), [&](Ref* render)
	{
		auto scene = SelectScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B(0, 255, 255)));
	});
	auto setting_item = MenuItemFont::create(ZH("| 游戏设置 |"), [&](Ref* render)
	{
		auto scene = SettingScene::createScene();
		Director::getInstance()->pushScene(scene);
	});
	auto close_item = MenuItemFont::create(ZH("| 退出游戏 |"), [&](Ref* render)
	{
		Director::getInstance()->end();
	});

	Vector<MenuItem*> menus;
	menus.pushBack(setting_item);
	menus.pushBack(select_item);
	menus.pushBack(close_item);
	auto menu = Menu::createWithArray(menus);
	menu->setPosition(visibleSize.width/2,visibleSize.height/5);
	this->addChild(menu, 1);
	menu->alignItemsHorizontally();

	auto label = Label::createWithTTF("Monopoly", "fonts/Marker Felt.ttf", 150);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + 4*visibleSize.height/5 - label->getContentSize().height));
	this->addChild(label, 1);
	return true;
}