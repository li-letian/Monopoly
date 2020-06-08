#include "ItemScene.h"
#include "MapScene.h"
#include "Character/Character.h"
#include "Common/CommonMethod.h"
#include "Item/Item.h"
using namespace std;

ItemScene* ItemScene::createScene(MapScene* map_scene) {
	auto item_layer = ItemScene::create();
	item_layer->map_scene_ = map_scene;
    item_layer->setPosition(Vec2(6000, 6000));
	//item_layer->map_scene_->addItemScene(item_layer);
	
	item_layer->map_scene_->addChild(item_layer, 23, "item_scene");
    item_layer->map_scene_->setMenuCallback("item", [=](Ref* ref) {item_layer->open(ref); });
	return item_layer;
}

bool ItemScene::init() {
	if (!Layer::init()) {
		return false;

	}
	posInit();
	auto sprite = Sprite::create("Item.png");
	sprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(sprite, 10);
	for (int i = 0; i < 4; i++) {
		item_vec_.push_back(vector<Item*>());
	}

	return true;
}

void ItemScene::updateMenu(Character* player) {
	auto item_sprite = this->getChildByName("sprite");
	item_sprite->retain();
	this->removeAllChildren();
	this->addChild(item_sprite, 24, "sprite");
	item_sprite->release();
	int tag = player->getTag();

	for (int i = 0; i < item_vec_[tag].size(); i++) {
		auto item_label = Label::createWithSystemFont(item_vec_[tag][i]->getItemName(), "fonts/arial.ttf", 34);
		auto item_label_menu_item = MenuItemLabel::create(item_label);
		item_label_menu_item->setCallback([=](Ref* render) {
			item_vec_[tag][i]->work(player);
			item_vec_[tag].erase(item_vec_[tag].begin() + i);
			});

		auto item_menu = Menu::create();
		item_menu->addChild(item_label_menu_item, 30);
		item_menu->setPosition(pos_vec_[i]);
		this->map_scene_->addChild(item_menu);
	}

}

void ItemScene::open(Ref* ref)
{
	this->setPosition(Vec2(0, 0));
	this->map_scene_->setMenuCallback("item", [=](Ref* ref) {close(ref); });
}

void ItemScene::close(Ref* ref)
{
	this->setPosition(Vec2(6000, 6000));
	this->map_scene_->setMenuCallback("item", [=](Ref* ref) {open(ref); });
}

void ItemScene::posInit() {
	pos_vec_.push_back(Vec2(20 , 550));
	pos_vec_.push_back(Vec2(165, 550));
	pos_vec_.push_back(Vec2(310, 550));
	pos_vec_.push_back(Vec2(455, 550));
	pos_vec_.push_back(Vec2(597, 550));   //第一行
	pos_vec_.push_back(Vec2(20 , 468));
	pos_vec_.push_back(Vec2(165, 468));
	pos_vec_.push_back(Vec2(310, 468));
	pos_vec_.push_back(Vec2(455, 468));
	pos_vec_.push_back(Vec2(597, 468));   //第二行
	pos_vec_.push_back(Vec2(20 , 388));
	pos_vec_.push_back(Vec2(165, 388));
	pos_vec_.push_back(Vec2(310, 388));
	pos_vec_.push_back(Vec2(455, 388));
	pos_vec_.push_back(Vec2(597, 388));   //第三行
	pos_vec_.push_back(Vec2(20 , 306));
	pos_vec_.push_back(Vec2(165, 306));
	pos_vec_.push_back(Vec2(310, 306));
	pos_vec_.push_back(Vec2(455, 306));
	pos_vec_.push_back(Vec2(597, 306));   //第四行
	pos_vec_.push_back(Vec2(20 , 226));
	pos_vec_.push_back(Vec2(165, 226));
	pos_vec_.push_back(Vec2(310, 226));
	pos_vec_.push_back(Vec2(455, 226));
	pos_vec_.push_back(Vec2(597, 226));   //第五行
	pos_vec_.push_back(Vec2(20 , 146));
	pos_vec_.push_back(Vec2(165, 146));
	pos_vec_.push_back(Vec2(310, 146));
	pos_vec_.push_back(Vec2(455, 146));
	pos_vec_.push_back(Vec2(597, 146));   //第六行

}