#include "Scene/SelectScene.h"
#include "Scene/StartScene.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "Common/CommonConstant.h"

Scene *SelectScene::createScene()
{
	return SelectScene::create();
}

bool SelectScene::transformToAi(int i, Ref *render, Sprite *ai, Sprite *player, MenuItemFont *item)
{
	if (i == 1)
		return false;
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto sound_effect = AudioEngine::play2d("bottom_down.mp3", false);
	is_ai_.at(i) = true;
	ai->setPosition(Vec2(visible_size.width * (1.5f + i) / 10.f, visible_size.height * 7.f / 10.f));
	player->setPosition(Vec2(visible_size.width * 10.f, visible_size.height * 10.f));

	item->setCallback([=](Ref *ref) { transformToPlayer(i, ref, ai, player, item); });
	return true;
}
bool SelectScene::transformToPlayer(int i, Ref *render, Sprite *ai, Sprite *player, MenuItemFont *item)
{
	if (i == 1)
		return false;
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto sound_effect = AudioEngine::play2d("bottom_down.mp3", false);
	is_ai_.at(i) = false;
	ai->setPosition(Vec2(visible_size.width * 10.f, visible_size.height * 10));
	player->setPosition(Vec2(visible_size.width * (1.5f + i) / 10.f, visible_size.height * 7.f / 10.f));
	item->setCallback([=](Ref *ref) { transformToAi(i, ref, ai, player, item); });
	return true;
}

bool SelectScene::addOption(int i)
{
	MenuItemFont::setFontName("fonts/STHUPO.ttf");
	MenuItemFont::setFontSize(25);
	auto visible_size = Director::getInstance()->getVisibleSize();

	auto avatar = Sprite::create(StringUtils::format("%s_avatar.png", player_name[i].c_str()));
	avatar->setAnchorPoint(Vec2(0.5, 0.5));
	avatar->setPosition(Vec2(visible_size.width * (1.5f + i) / 10.f, visible_size.height * 9.f / 10.f));
	this->addChild(avatar, 20);

	auto label = Label::createWithSystemFont(player_name[i], "fonts/arial.ttf", 22);
	label->setTextColor(Color4B::WHITE);
	label->setAnchorPoint(Vec2(0.5, 0.5));
	label->setPosition(Vec2(visible_size.width * (1.5f + i) / 10.f, visible_size.height * 8.f / 10.f));
	this->addChild(label, 26);
	auto ai = Sprite::create("ai_image.png");
	ai->setAnchorPoint(Vec2(0.5, 0.5));
	ai->setPosition(Vec2(visible_size.width * 10.f, visible_size.height * 10.f));
	this->addChild(ai, 50);
	auto player = Sprite::create("player_image.png");
	player->setAnchorPoint(Vec2(0.5, 0.5));
	player->setPosition(Vec2(visible_size.width * (1.5f + i) / 10.f, visible_size.height * 7.f / 10.f));
	this->addChild(player, 50);

	if (i == 1)
		return true;
	auto item = MenuItemFont::create("Switch");
	item->setCallback([=](Ref *render) {
		transformToAi(i, render, ai, player, item);
	});
	item->setPosition(Vec2(visible_size.width * (1.5f + i) / 10.f, visible_size.height * 6.f / 10.f));

	auto menu = Menu::create(item, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 5);
	return true;
}

bool SelectScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("selectbackground.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(origin);
	this->addChild(background, 0);

	MenuItemFont::setFontName("fonts/STHUPO.ttf");
	MenuItemFont::setFontSize(50);

	for (int i = 1; i <= 7; i++)
		is_ai_.push_back(false);
	for (int i = 1; i <= 6; i++)
	{
		addOption(i);
	}

	MenuItemFont::setFontName("fonts/STHUPO.ttf");
	MenuItemFont::setFontSize(50);

	auto exit_item = MenuItemFont::create("Exit", [=](Ref *render) {
		auto sound_effect = AudioEngine::play2d("bottom_down.mp3", false);
		AudioEngine::stopAll();
		auto scene = StartScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B(0, 255, 255)));
	});
	auto start_item = MenuItemFont::create("Start", [=](Ref *render) {
		auto sound_effect = AudioEngine::play2d("bottom_down.mp3", false);
		auto temp = GameController::create(this->is_ai_);
	});

	float x = origin.x + visible_size.width / 7;
	float y = origin.y + visible_size.width / 5;
	start_item->setPosition(Vec2(x, y));

	x = origin.x + visible_size.width * 6 / 7;
	y = origin.y + visible_size.width / 5;
	exit_item->setPosition(Vec2(x, y));

	Vector<MenuItem *> menus;
	menus.pushBack(start_item);
	menus.pushBack(exit_item);
	auto menu = Menu::createWithArray(menus);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}