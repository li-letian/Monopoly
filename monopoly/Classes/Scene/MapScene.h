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

	//����������Խ���ͼ��С��ͼ��ת��������ڵ�ͼ���½�ê��GL���귽��ĵ�Ϊ���ĵ��ӽ�
	bool perspectiveJump(float x, float y);
	bool perspectiveJump(cocos2d::Vec2 p);

	//���ص�ͼ�ϵ�(index%��λ����)��λ������ڵ�ͼ���½�ê���GL��������
	cocos2d::Vec2 pos(int index)const
	{
		auto size = pos_.size();
		return pos_.at(index % size);
	}

	//���ص�ͼ��λ������
	std::size_t totalPosition()const
	{
		return pos_.size();
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