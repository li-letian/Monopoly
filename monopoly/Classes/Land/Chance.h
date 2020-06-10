#ifndef _CHANCE_H_
#define _CHANCE_H_

#include "cocos2d.h"
#include "Land.h"

#include<string>

USING_NS_CC;
class Character;
class Chance : public Land {
protected:

public:
	virtual bool onLand(Character* standing) override;
	static Chance* create(int index);

};

#endif // !_CHANCE_H_
