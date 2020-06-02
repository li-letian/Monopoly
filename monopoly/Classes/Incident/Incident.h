#ifndef  _INCIDENT_H_
#define _INCIDENT_H_

#include "Character/Character.h"
#include "cocos2d.h"
#include "Scene/MapScene.h"
USING_NS_CC;

class Incident {
public:
	Incident(MapScene* map_scene);
	virtual ~Incident() = default;
	virtual bool eventTrigger(Character* character) = 0;	//事件触发的接口
protected:
	MapScene* map_scene_ = nullptr;		//地图
	Character* character_ = nullptr;	//事件的操作对象角色
};

#endif