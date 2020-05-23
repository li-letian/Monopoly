#include "Scene/StartScene.h"
#include "Scene/MapScene.h"
#include "Scene/SettingScene.h"
#include "ZH.h"
USING_NS_CC;

Scene* MapScene::createScene()
{
	return MapScene::create();
}


bool MapScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	MenuItemFont::setFontName("华文琥珀");
	MenuItemFont::setFontSize(15);
	
	if (!MapScene::panelInit())
	{
		return false;
	}
	if (!MapScene::mapInit())
	{
		return false;
	}
	if (!MapScene::rollMap())
	{
		return false;
	}
	return true;
}

//初始化地图
bool MapScene::mapInit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	map = TMXTiledMap::create("gamemap.tmx");
	map->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	map->setPosition(0,visibleSize.height);

	
	map->getLayer("grass")->setLocalZOrder(-1);
	
	this->addChild(map, -1, "map");
	

	return true;
}

//添加地图滚动
bool MapScene::rollMap()
{
	auto listener = EventListenerTouchOneByOne::create();
	static Vec2 start_pos;
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		auto target = event->getCurrentTarget();
		start_pos = target->getPosition() - touch->getLocation();
		return true;
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event)
	{
		auto target = event->getCurrentTarget();
		target->setPosition(start_pos + touch->getLocation());
	};
	map->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, map);

	return true;
}

//初始化地图旁边的面板和上面的按钮们
bool MapScene::panelInit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//地图边用来交互的上面的菜单和右面的面板，包括进入道具的界面，时间的界面，各种界面的按钮
	this->panel = Layer::create();
	panel->setAnchorPoint(Vec2(0, 0));
	panel->setPosition(Vec2::ZERO);
	this->addChild(panel, 10);

	//创建按钮
	menu_item.insert("close", MenuItemFont::create(ZH("退出")));
	menu_item.insert("setting", MenuItemFont::create(ZH("设置")));
	menu_item.insert("item", MenuItemFont::create(ZH("道具")));
	menu_item.insert("stock", MenuItemFont::create(ZH("股票")));

	//从这个menu_item的Map中获取每个按钮的指针
	auto close_item = menu_item.at("close");
	auto setting_item = menu_item.at("setting");
	auto item_item = menu_item.at("item");
	auto stock_item = menu_item.at("stock");

	//设定按钮的显示位置
	auto menu = Menu::create();
	menu->addChild(item_item, 30);
	menu->addChild(close_item, 30);
	menu->addChild(setting_item, 30);
	menu->addChild(stock_item, 30);
	menu->setPosition(Vec2(visibleSize.width*2/5,visibleSize.height*14/15));
	panel->addChild(menu, 20);

	menu->alignItemsHorizontally();

	//这里可以通过setCallback这个函数任意更改按钮按下去后执行的回调函数
	close_item->setCallback([=](Ref* render)
	{
		auto scene = StartScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B(0, 255, 255)));
	});

	setting_item->setCallback([=](Ref* render)
	{
		auto scene = SettingScene::createScene();
		Director::getInstance()->pushScene(scene);
	});

	return true;
}