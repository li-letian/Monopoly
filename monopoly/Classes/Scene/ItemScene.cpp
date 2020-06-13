#include "ItemScene.h"
#include "MapScene.h"
#include "Character/Character.h"
#include "Scene/GameController.h"
#include "Common/CommonMethod.h"
#include "Item/Item.h"
#include "Incident/PopUpLayer.h"
#include "Item/Frame.h"
#include "Item/AngelCard.h"
#include "Item/BlackCard.h"
#include "Item/Car.h"
#include "Item/Motor.h"
#include "Item/HouseChange.h"
#include "Item/RedCard.h"
#include "Item/Turtle.h"
#include "Item/TurnAround.h"
#include "AudioEngine.h"
#include "Item/Sleep.h"
using namespace std;

ItemScene *ItemScene::createScene(MapScene *map_scene, GameController *game_controller)
{
	auto item_layer = ItemScene::create();
	item_layer->map_scene_ = map_scene;
	item_layer->game_controller_ = game_controller;
	item_layer->setPosition(Vec2(6000, 6000));
	//item_layer->map_scene_->addItemScene(item_layer);
	item_layer->map_scene_->addChild(item_layer, 23, "item_scene");
	item_layer->map_scene_->setMenuCallback("item", [=](Ref *ref) { item_layer->open(ref); });

	auto visible_size = Director::getInstance()->getVisibleSize();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = [=](Touch *touch, Event *event) {
		if (item_layer->is_open_)
		{
			if (touch->getLocation().x > visible_size.height)
				listener->setSwallowTouches(false);
			else
				listener->setSwallowTouches(true);
		}
		else
		{
			listener->setSwallowTouches(false);
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, item_layer);

	//添加原本就有的道具
	//auto characters = item_layer->game_controller_->getCharacters();
	//item_layer->addItem(characters.at(0), BlackCard::create());
	//item_layer->addItem(characters.at(0), Car::create());
	//item_layer->addItem(characters.at(0), Motor::create());
	//item_layer->addItem(characters.at(0), HouseChange::create());
	//item_layer->addItem(characters.at(0), RedCard::create());
	//item_layer->addItem(characters.at(0), Turtle::create());
	//item_layer->addItem(characters.at(0), TurnAround::create());
	//item_layer->addItem(characters.at(0), Sleep::create());

	return item_layer;
}

bool ItemScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	posInit();
	auto sprite = Sprite::create("Item.png");
	sprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(sprite, 10);
	for (int i = 0; i < 4; i++)
	{
		item_vec_.push_back(vector<Item *>());
	}
	return true;
}

int ItemScene::getItemSize(Character *player)
{
	auto tag = player->getTag();
	return item_vec_.at(tag).size();
}

void ItemScene::addItem(Character *player, Item *item)
{
	auto tag = player->getTag();
	game_controller_->addChild(item, 600);
	item_vec_.at(tag).push_back(item);
}

void ItemScene::removeItem(Character *player, Item *item)
{
	auto tag = player->getTag();
	item->removeFromParentAndCleanup(true);
	auto &vec = item_vec_.at(tag);
	vec.erase(std::find(vec.begin(), vec.end(), item));
}

Item *ItemScene::getItem(Character *player, std::string name)
{
	auto tag = player->getTag();
	auto &vec = item_vec_.at(tag);
	for (auto item : vec)
	{
		if (item->getItemName() == name)
		{
			return item;
		}
	}
	return nullptr;
}

void ItemScene::updateMenu(Character *player)
{
	this->removeAllChildren();
	auto item_sprite = Sprite::create("Item.png");
	item_sprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(item_sprite, 24, "sprite");
	int tag = player->getTag();

	for (decltype(item_vec_[tag].size()) i = 0; i < item_vec_[tag].size(); i++)
	{
		auto item_label = Label::createWithSystemFont(ZH(item_vec_[tag][i]->getItemName()), "fonts/arial.ttf", 34);
		auto item_label_menu_item = MenuItemLabel::create(item_label);

		item_label_menu_item->setCallback([=](Ref *render) {
			auto pop = PopUpLayer::create();
			pop->setTitle(std::string("道具"));
			pop->setContent("使用" + item_vec_[tag][i]->getItemName() + "道具\n" + item_vec_[tag][i]->getContent());

			pop->setCallBack([=](Ref *ref) {
				item_vec_[tag][i]->work(player);
				item_vec_[tag][i]->removeFromParentAndCleanup(true);
				item_vec_[tag].erase(item_vec_[tag].begin() + i);
				this->updateMenu(player);
			});
			pop->setPosition(Vec2(0, 0));
			close(nullptr);
			map_scene_->addChild(pop, 52);
		});
		item_label_menu_item->setAnchorPoint(Vec2(0, 0.5));
		auto item_menu = Menu::create();
		item_menu->addChild(item_label_menu_item, 30);
		item_menu->setAnchorPoint(Vec2(0, 0.5));
		item_menu->setPosition(pos_vec_[i]);
		this->addChild(item_menu, 30);
	}
}

void ItemScene::open(Ref *ref)
{
	is_open_ = true;
	auto soundEffectID = AudioEngine::play2d("bottom_down.mp3", false);
	this->setPosition(Vec2(0, 0));
	this->map_scene_->setMenuCallback("item", [=](Ref *ref) { close(ref); });
}

void ItemScene::close(Ref *ref)
{
	is_open_ = false;
	auto soundEffectID = AudioEngine::play2d("bottom_down.mp3", false);
	this->setPosition(Vec2(6000, 6000));
	this->map_scene_->setMenuCallback("item", [=](Ref *ref) { open(ref); });
}

void ItemScene::posInit()
{
	pos_vec_.push_back(Vec2(20, 550));
	pos_vec_.push_back(Vec2(165, 550));
	pos_vec_.push_back(Vec2(310, 550));
	pos_vec_.push_back(Vec2(455, 550));
	pos_vec_.push_back(Vec2(597, 550)); //第一行
	pos_vec_.push_back(Vec2(20, 468));
	pos_vec_.push_back(Vec2(165, 468));
	pos_vec_.push_back(Vec2(310, 468));
	pos_vec_.push_back(Vec2(455, 468));
	pos_vec_.push_back(Vec2(597, 468)); //第二行
	pos_vec_.push_back(Vec2(20, 388));
	pos_vec_.push_back(Vec2(165, 388));
	pos_vec_.push_back(Vec2(310, 388));
	pos_vec_.push_back(Vec2(455, 388));
	pos_vec_.push_back(Vec2(597, 388)); //第三行
	pos_vec_.push_back(Vec2(20, 306));
	pos_vec_.push_back(Vec2(165, 306));
	pos_vec_.push_back(Vec2(310, 306));
	pos_vec_.push_back(Vec2(455, 306));
	pos_vec_.push_back(Vec2(597, 306)); //第四行
	pos_vec_.push_back(Vec2(20, 226));
	pos_vec_.push_back(Vec2(165, 226));
	pos_vec_.push_back(Vec2(310, 226));
	pos_vec_.push_back(Vec2(455, 226));
	pos_vec_.push_back(Vec2(597, 226)); //第五行
	pos_vec_.push_back(Vec2(20, 146));
	pos_vec_.push_back(Vec2(165, 146));
	pos_vec_.push_back(Vec2(310, 146));
	pos_vec_.push_back(Vec2(455, 146));
	pos_vec_.push_back(Vec2(597, 146)); //第六行
}