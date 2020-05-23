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

	MenuItemFont::setFontName("��������");
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

//��ʼ����ͼ
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

//��ӵ�ͼ����
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

//��ʼ����ͼ�Աߵ���������İ�ť��
bool MapScene::panelInit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ͼ����������������Ĳ˵����������壬����������ߵĽ��棬ʱ��Ľ��棬���ֽ���İ�ť
	this->panel = Layer::create();
	panel->setAnchorPoint(Vec2(0, 0));
	panel->setPosition(Vec2::ZERO);
	this->addChild(panel, 10);

	//������ť
	menu_item.insert("close", MenuItemFont::create(ZH("�˳�")));
	menu_item.insert("setting", MenuItemFont::create(ZH("����")));
	menu_item.insert("item", MenuItemFont::create(ZH("����")));
	menu_item.insert("stock", MenuItemFont::create(ZH("��Ʊ")));

	//�����menu_item��Map�л�ȡÿ����ť��ָ��
	auto close_item = menu_item.at("close");
	auto setting_item = menu_item.at("setting");
	auto item_item = menu_item.at("item");
	auto stock_item = menu_item.at("stock");

	//�趨��ť����ʾλ��
	auto menu = Menu::create();
	menu->addChild(item_item, 30);
	menu->addChild(close_item, 30);
	menu->addChild(setting_item, 30);
	menu->addChild(stock_item, 30);
	menu->setPosition(Vec2(visibleSize.width*2/5,visibleSize.height*14/15));
	panel->addChild(menu, 20);

	menu->alignItemsHorizontally();

	//�������ͨ��setCallback�������������İ�ť����ȥ��ִ�еĻص�����
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