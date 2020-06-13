#ifndef _SELECT_SCENE_H_
#define _SELECT_SCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class SelectScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SelectScene);
};

#endif