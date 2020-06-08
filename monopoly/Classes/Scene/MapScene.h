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
	bool rollMap();
	bool panelInit();
	bool miniMapInit();
	bool informationInit();
	virtual bool init();

	CREATE_FUNC(MapScene);


	//����������Խ���ͼ��С��ͼ��ת��������ڵ�ͼ���½�ê��GL���귽��ĵ�Ϊ���ĵ��ӽ�
	bool perspectiveJump(float x, float y);
	bool perspectiveJump(cocos2d::Vec2 p);
	void setInfoOnDisplay(Character* player);
	void addItemScene(ItemScene* item_scene);
	void updateInformation(Character* player);
	void updateDay();
	//���ص�ͼ�ϵ�(index%��λ����)��λ������ڵ�ͼ���½�ê���GL��������
	cocos2d::Vec2 pos(int index)
	{
		auto size = pos_.size();
		return pos_.at(index % size);
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

	//���ص�ͼ��λ������
	int totalPosition()
	{
		return static_cast<int>(pos_.size());
	}

	//Ϊ����Ϲ���Ϊname�İ�ť���ûص�����
	//name���У�
	//���� item
	//���� stock
	bool setMenuCallback(const std::string &name,std::function<void(Ref* render)>fun)
	{
		menu_item_.at(name)->setCallback(fun);
		return true;
	}


	//���ص�ͼ
	cocos2d::TMXTiledMap* getMap()
	{
		return map_;
	}
	
	//����С��ͼ����ΪС��ͼ������ʾ��ʱ������ŵģ����Կ��Է��ĵ�ʹ�úʹ��ͼ��ͬ�ߴ������addchild��setposition
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