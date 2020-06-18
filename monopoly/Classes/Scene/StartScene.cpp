#include "Scene/StartScene.h"
#include "Scene/SelectScene.h"
#include "Scene/SettingScene.h"
#include "Common/CommonMethod.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	return StartScene::create();
}


void StartScene::music_open(MenuItem* setting_item)
{
	auto bgm_sound = AudioEngine::play2d("BGM.mp3", true);
	AudioEngine::setVolume(bgm_sound, 0.4f);
	setting_item->setCallback([=](Ref* ref) {music_close( setting_item); });
}


void StartScene::music_close(MenuItem* setting_item)
{
	AudioEngine::stopAll();
	setting_item->setCallback([=](Ref* ref) {music_open(setting_item); });
}



bool StartScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto bgm_sound = AudioEngine::play2d("BGM.mp3", true);
	AudioEngine::setVolume(bgm_sound, 0.4f);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("startbackground.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(origin);
	this->addChild(background, 0);

	MenuItemFont::setFontName("华文琥珀");
	MenuItemFont::setFontSize(40);

	auto select_item = MenuItemFont::create(ZH("| 开始游戏 |"), [=](Ref* render)
	{
		auto sound_effect = AudioEngine::play2d("bottom_down.mp3", false);
		auto scene = SelectScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B(0, 255, 255)));
	});
	auto setting_item = MenuItemFont::create(ZH("| 背景音乐 |"));
	setting_item->setCallback([=](Ref* render)
	{
		auto sound_effect = AudioEngine::play2d("bottom_down.mp3", false);
		music_close(setting_item);
	});
	auto close_item = MenuItemFont::create(ZH("| 退出游戏 |"), [=](Ref* render)
	{
		auto sound_effect = AudioEngine::play2d("bottom_down.mp3", false);
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