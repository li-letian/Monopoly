#ifndef _GOD_H_
#define _GOD_H_
#include "cocos2d.h"

USING_NS_CC;

class MapScene;
class Character;
class God : public: Sprite{
public:
	virtual bool onLand(Character* standing)
	{
		return true;
	}

protected:
	int index_ = 0;
};




#endif