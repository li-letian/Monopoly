#ifndef _AVIATION_H_
#define _AVIATION_H_

#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonMethod.h"
#include "Scene/StorkScene.h"

#include<string>

USING_NS_CC;

class Aviation : public Land {
protected:
	std::string name_;

public:
	virtual bool onLand(Character* standing) override;
	static Aviation* create(MapScene* map_scene, int index);

};

#endif // !_AVIATION_H_
