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
	virtual bool eventTrigger(Character* character) = 0;	//�¼������Ľӿ�
protected:
	MapScene* map_scene_ = nullptr;		//��ͼ
	Character* character_ = nullptr;	//�¼��Ĳ��������ɫ
};

#endif