#ifndef _MAP_SCENE_H_
#define _MAP_SCENE_H_

#include "cocos2d.h"
#include <string>
#include <vector>

class MapScene : public cocos2d::Scene
{
public:
	static MapScene* createScene();

	bool mapInit();
	bool landInit();
	bool rollMap();
	bool panelInit();
	virtual bool init();

	CREATE_FUNC(MapScene);

	cocos2d::Layer* panel_=nullptr;
	cocos2d::TMXTiledMap* map_ = nullptr;
	cocos2d::Map<std::string, cocos2d::MenuItem*>menu_item_;
	std::vector<cocos2d::Vec2>pos_;
	std::vector<int>type_;
};



#endif