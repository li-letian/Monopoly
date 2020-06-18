#ifndef _START_SCENE_H_
#define _START_SCENE_H_

#include "cocos2d.h"

class StartScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void music_open( cocos2d::MenuItem* setting_item);
	void music_close( cocos2d::MenuItem* setting_item);

	CREATE_FUNC(StartScene);
};

#endif