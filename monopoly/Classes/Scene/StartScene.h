#ifndef _START_SCENE_H_
#define _START_SCENE_H_

#include "cocos2d.h"

class StartScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(StartScene);
};

#endif