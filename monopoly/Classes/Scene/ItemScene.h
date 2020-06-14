#ifndef  _ITEM_SCENE_H_
#define  _ITEM_SCNEN_H_
#include "cocos2d.h"
#include <vector>
#include "Character/Character.h"
#include "MapScene.h"
using namespace std;
using namespace cocos2d;
class Item;
class GameController;
class ItemScene : public Layer {
public:
	friend class ItemScene;
	static ItemScene* ItemScene::createScene(MapScene* map_scene, GameController* game_controller);
	virtual bool init();
	void posInit();
	void updateMenu(Character* player);
	void open(Ref* ref);
	void close(Ref* ref);
	CREATE_FUNC(ItemScene);

	//因为cocos的内存机制，所以我们加道具的时候不能直接push，要调用这个addItem保护道具被addchild了
	//被使用的道具会自动removeFromParentWithCleanup
	void addItem(Character* player, Item* item);
	Item* getItem(Character* player,std::string name);
	void removeItem(Character* player, Item* item);
	int getItemSize(Character* player);

protected:
	bool is_open_ = false;
	MapScene* map_scene_=nullptr;
	GameController* game_controller_ = nullptr;
	vector<vector<Item* >> item_vec_;
	vector<cocos2d::Vec2>pos_vec_;
};



#endif