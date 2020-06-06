#include "ItemScene.h"
#include "MapScene.h"
#include "Character/Character.h"
#include "Common/CommonMethod.h"
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
	
	return true;
}

void ItemScene::updateMenu(Character* player) {
	this->removeAllChildren();

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