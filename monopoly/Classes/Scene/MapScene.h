#ifndef _MAP_SCENE_H_
#define _MAP_SCENE_H_

#include "cocos2d.h"
#include <string>
#include <vector>
#include <functional>

class MapScene : public cocos2d::Scene
{
protected:
	cocos2d::Layer* panel_ = nullptr;
	cocos2d::TMXTiledMap* map_ = nullptr;
	cocos2d::TMXTiledMap* mini_map_ = nullptr;

	cocos2d::Map<std::string, cocos2d::MenuItem*>menu_item_;
	std::vector<cocos2d::Vec2>pos_;
	std::vector<int>type_;

public:
	static MapScene* createScene();
	bool mapInit();
	bool landInit();
	bool rollMap();
	bool panelInit();
	bool miniMapInit();
	virtual bool init();
	CREATE_FUNC(MapScene);

	//这个函数可以将地图和小地图跳转到以相对于地图左下角锚点GL坐标方向的点为中心的视角
	bool perspectiveJump(float x, float y);
	bool perspectiveJump(cocos2d::Vec2 p);

	//返回地图上第(index%总位置数)个位置相对于地图左下角锚点的GL方向坐标
	cocos2d::Vec2 pos(int index)const
	{
		auto size = pos_.size();
		return pos_.at(index % size);
	}

	//返回地图上位置总数
	std::size_t totalPosition()const
	{
		return pos_.size();
	}

	//为面板上功能为name的按钮设置回调函数
	//name表列：
	//道具 item
	//股市 stock
	bool setMenuCallback(const std::string &name,std::function<void(Ref* render)>fun)
	{
		menu_item_.at(name)->setCallback(fun);
		return true;
	}
	
	cocos2d::TMXTiledMap* getMap()const
	{
		return map_;
	}
	
	cocos2d::TMXTiledMap* getMiniMap()const
	{
		return mini_map_;
	}
	cocos2d::Layer* getPanel()const
	{
		return panel_;
	}

};



#endif