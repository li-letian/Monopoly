#ifndef _SETTING_SCENE_H_
#define _SETTING_SCENE_H_

#include "cocos2d.h"

class SettingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SettingScene);
};

#endif