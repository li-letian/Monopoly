#ifndef _LAND_H_
#define _LAND_H_

#include "cocos2d.h"
#include "Character/Character.h"

USING_NS_CC;

class MapScene;
class Land : public Sprite {
public:
	virtual bool onLand(Character* standing)
	{
		return true;
	}
	virtual bool byLand(Character* standing)
	{
		return true;
	}
	std::string getName()
	{
		return name_;
	}

protected:
	std::string name_;
	int index_ = 0;
};

#endif // !_LAND_H_
