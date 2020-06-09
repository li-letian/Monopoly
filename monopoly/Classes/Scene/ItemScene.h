#ifndef  _ITEM_SCENE_H_
#define  _ITEM_SCNEN_H_
#include "cocos2d.h"
#include <vector>
#include "Character/Character.h"
#include "MapScene.h"
using namespace std;
using namespace cocos2d;
class Item;
class ItemScene : public Layer {
public:
	static ItemScene* ItemScene::createScene(MapScene* map_scene);
	virtual bool init();
	void posInit();
	void updateMenu(Character* player);
	void open(Ref* ref);
	void close(Ref* ref);
	CREATE_FUNC(ItemScene);

	void addItem(Character* player, Item* item);
	

protected:
	MapScene* map_scene_=nullptr;
	vector<vector<Item* >> item_vec_;
	vector<cocos2d::Vec2>pos_vec_;
};








#endif