#ifndef _ITEM_H_
#define _ITEM_H_
#include "cocos2d.h"

USING_NS_CC;

class Character;
class Item : public: Sprite{
public:
	virtual bool work()
	{
		return true;
	}
	
protected:
	Character* owner;
	int index_ = 0;
}


























#endif