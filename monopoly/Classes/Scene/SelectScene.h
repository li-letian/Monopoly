#ifndef _SELECT_SCENE_H_
#define _SELECT_SCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class SelectScene : public cocos2d::Scene
{
protected:
	std::vector<bool>is_ai_;
	bool transformToAi(int i, Ref* render, Sprite* ai, Sprite* player, MenuItemFont* item);
	bool transformToPlayer(int i, Ref* render, Sprite* ai, Sprite* player, MenuItemFont* item);

public:
	static cocos2d::Scene* createScene();
	bool addOption(int i);
	virtual bool init();

	CREATE_FUNC(SelectScene);
};

#endif