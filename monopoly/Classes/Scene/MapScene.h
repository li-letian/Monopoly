#ifndef _MAP_SCENE_H_
#define _MAP_SCENE_H_

#include "cocos2d.h"
#include <string>


class MapScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool mapInit();
	bool rollMap();
	bool panelInit();
	virtual bool init();

	CREATE_FUNC(MapScene);

protected:
	cocos2d::Layer* panel=nullptr;
	cocos2d::TMXTiledMap* map;
	cocos2d::Map<std::string, cocos2d::MenuItem*>menu_item;
};



#endif