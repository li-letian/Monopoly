#ifndef  _ITEM_SCENE_H_
#define  _ITEM_SCNEN_H_
#include "cocos2d.h"
#include <vector>
#include "Character/Character.h"
using namespace std;
using namespace cocos2d;

class ItemScene : public Layer {
public:
	static ItemScene* ItemScene::createScene(MapScene* map_scene);
	virtual bool init();

	void updateMenu(Character* player);
	void open(Ref* ref);
	void close(Ref* ref);
	CREATE_FUNC(ItemScene);
protected:
	MapScene* map_scene_;
};








#endif