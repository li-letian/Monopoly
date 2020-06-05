#ifndef _HOSPITAL_H_
#define _HOSPITAL_H_

#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"

#include<string>

USING_NS_CC;

class Hospital : public Land {
protected:
	std::string name_;

public:
	virtual bool onLand(Character* standing) override;
	static Hospital* create(MapScene* map_scene, int index);

};

#endif // !_HOSPITAL_H_
