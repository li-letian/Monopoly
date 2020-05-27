#ifndef _MAP_SCENE_H_
#define _MAP_SCENE_H_

#include "cocos2d.h"
#include <string>
#include <vector>

class MapScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool mapInit();
	bool landInit();
	bool rollMap();
	bool panelInit();
	virtual bool init();

	//这个函数可以将地图和小地图视角跳转到相应的位置，可能在回合开始的时候需要调用一下
	bool perspectiveJump(float x, float y);

	CREATE_FUNC(MapScene);

	cocos2d::Layer* panel_=nullptr;
	cocos2d::TMXTiledMap* map_ = nullptr;
	cocos2d::Map<std::string, cocos2d::MenuItem*>menu_item_;

	//下面的vector是关于下标位置的一些信息
	std::vector<cocos2d::Vec2>pos_;
	std::vector<int>type_;
	
};



#endif