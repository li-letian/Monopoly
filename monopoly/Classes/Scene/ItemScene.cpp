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
#include "Item/Sleep.h"
using namespace std;

ItemScene *ItemScene::createScene(MapScene *map_scene)
{
	auto item_layer = ItemScene::create();
	item_layer->map_scene_ = map_scene;
	item_layer->setPosition(Vec2(6000, 6000));
	//item_layer->map_scene_->addItemScene(item_layer);

	item_layer->map_scene_->addChild(item_layer, 23, "item_scene");
	item_layer->map_scene_->setMenuCallback("item", [=](Ref *ref) { item_layer->open(ref); });
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
	Frame *A = Frame::create();
	item_vec_[1].push_back(BlackCard::create());
	item_vec_[1].push_back(Car::create());
	item_vec_[1].push_back(Motor::create());
	item_vec_[1].push_back(HouseChange::create());
	item_vec_[1].push_back(RedCard::create());
	item_vec_[1].push_back(Turtle::create());
	item_vec_[1].push_back(TurnAround::create());
	item_vec_[1].push_back(HolidayCard::create());
	return true;
}

void ItemScene::addItem(Character *player, Item *item)
{
	auto tag = player->getTag();
	GetGameController()->addChild(item, 600);
	item_vec_.at(tag).push_back(item);
}

void ItemScene::updateMenu(Character *player)
{
	this->removeAllChildren();
	auto item_sprite = Sprite::create("Item.png");
	item_sprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(item_sprite, 24, "sprite");
	int tag = player->getTag();

	for (int i = 0; i < item_vec_[tag].size(); i++)
	{
		auto item_label = Label::createWithSystemFont(ZH(item_vec_[tag][i]->getItemName()), "fonts/arial.ttf", 34);
		auto item_label_menu_item = MenuItemLabel::create(item_label);

		item_label_menu_item->setCallback([=](Ref *render) {
			auto pop = PopUpLayer::create();
			pop->setTitle(std::string("����"));
			pop->setContent("ʹ��" + item_vec_[tag][i]->getItemName() + "����\n" + item_vec_[tag][i]->getContent());

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
	this->setPosition(Vec2(0, 0));
	this->map_scene_->setMenuCallback("item", [=](Ref *ref) { close(ref); });
}

void ItemScene::close(Ref *ref)
{
	this->setPosition(Vec2(6000, 6000));
	this->map_scene_->setMenuCallback("item", [=](Ref *ref) { open(ref); });
}

void ItemScene::posInit()
{
	pos_vec_.push_back(Vec2(20, 550));
	pos_vec_.push_back(Vec2(165, 550));
	pos_vec_.push_back(Vec2(310, 550));
	pos_vec_.push_back(Vec2(455, 550));
	pos_vec_.push_back(Vec2(597, 550)); //��һ��
	pos_vec_.push_back(Vec2(20, 468));
	pos_vec_.push_back(Vec2(165, 468));
	pos_vec_.push_back(Vec2(310, 468));
	pos_vec_.push_back(Vec2(455, 468));
	pos_vec_.push_back(Vec2(597, 468)); //�ڶ���
	pos_vec_.push_back(Vec2(20, 388));
	pos_vec_.push_back(Vec2(165, 388));
	pos_vec_.push_back(Vec2(310, 388));
	pos_vec_.push_back(Vec2(455, 388));
	pos_vec_.push_back(Vec2(597, 388)); //������
	pos_vec_.push_back(Vec2(20, 306));
	pos_vec_.push_back(Vec2(165, 306));
	pos_vec_.push_back(Vec2(310, 306));
	pos_vec_.push_back(Vec2(455, 306));
	pos_vec_.push_back(Vec2(597, 306)); //������
	pos_vec_.push_back(Vec2(20, 226));
	pos_vec_.push_back(Vec2(165, 226));
	pos_vec_.push_back(Vec2(310, 226));
	pos_vec_.push_back(Vec2(455, 226));
	pos_vec_.push_back(Vec2(597, 226)); //������
	pos_vec_.push_back(Vec2(20, 146));
	pos_vec_.push_back(Vec2(165, 146));
	pos_vec_.push_back(Vec2(310, 146));
	pos_vec_.push_back(Vec2(455, 146));
	pos_vec_.push_back(Vec2(597, 146)); //������
}