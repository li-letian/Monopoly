#ifndef _MAP_SCENE_H_
#define _MAP_SCENE_H_

#include "cocos2d.h"
#include <string>
#include <vector>
#include <functional>
class Land;
class Character;
class Stock;
class ItemScene;
class God;
class MapScene : public cocos2d::Scene
{
protected:
	cocos2d::Layer* panel_=nullptr;
	cocos2d::TMXTiledMap* map_=nullptr;
	cocos2d::TMXTiledMap* mini_map_ = nullptr ;
	

	cocos2d::Map<std::string, cocos2d::MenuItem*>menu_item_;
	std::vector<cocos2d::Vec2>pos_;
	std::map<int,int>idx_;
	std::vector<int>type_;
	std::vector<Land*>lands_;
	std::vector<God*>gods_;

	int year_ = 1;
	int month_ = 1;
	int day_ = 1;

	int info_on_display_ = 0;
	ItemScene* item_scene_ = nullptr;
    


public:

	static MapScene* createScene();
	bool mapInit();
	bool landInit();
	bool touchInit();
	bool rollMap();
	bool panelInit();
	bool miniMapInit();
	bool informationInit();
	virtual bool init();

	CREATE_FUNC(MapScene);


	//这个函数可以将地图和小地图跳转到以相对于地图左下角锚点GL坐标方向的点为中心的视角
	bool perspectiveJump(float x, float y);
	bool perspectiveJump(cocos2d::Vec2 p);
	void setInfoOnDisplay(Character* player);
	void addItemScene(ItemScene* item_scene);
	void updateInformation(Character* player);
	void updateDay();
	//返回地图上第(index%总位置数)个位置相对于地图左下角锚点的GL方向坐标
	cocos2d::Vec2 pos(int index)
	{
		auto size = pos_.size();
		return pos_.at(index % size);
	}

	//传入一个相对于屏幕左下角的position位置，他会返回当前位置在地图上的编号
	//如果这个位置不在路上，那么会返回-1，注意一下特殊判断
	int touchIndex(cocos2d::Vec2 touch_position)
	{
		touch_position -= map_->getPosition();
		auto tile_size = map_->getTileSize();
		auto map_size = map_->getMapSize();
		touch_position.y = tile_size.height * map_size.height - touch_position.y;
		auto x = static_cast<int>(touch_position.x /tile_size.width);
		auto y = static_cast<int>(touch_position.y / tile_size.height);
		if (x % 2==1) x++;
		if (y % 2==1) y++;
		int index = (x * 100 + y) % 10000;
		return idx_.count(index) ? idx_.at(index) :-1;
	}

	Land*& getLand(int index)
	{
		auto size = pos_.size();
		return lands_.at(index % size);
	}
	God*& getGod(int index)
	{
		auto size = pos_.size();
		return gods_.at(index % size);
	}

	int getType(int index)
	{
		auto size = pos_.size();
		return type_.at(index % size);
	}

	//返回地图上位置总数
	int totalPosition()
	{
		return static_cast<int>(pos_.size());
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


	//返回地图
	cocos2d::TMXTiledMap* getMap()
	{
		return map_;
	}
	
	//返回小地图，因为小地图是在显示的时候才缩放的，所以可以放心的使用和大地图相同尺寸的坐标addchild和setposition
	cocos2d::TMXTiledMap* getMiniMap()
	{
		return mini_map_;
	}
	cocos2d::Layer* getPanel()
	{
		return panel_;
	}

};



#endif