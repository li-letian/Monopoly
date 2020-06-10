#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "Item/Item.h"
#include "cocos2d.h"
USING_NS_CC;
class Character;
class Missile : public Item {	//µÀ¾ßÃû³Æ
public:
	virtual void work(Character* player);
	CREATE_FUNC(Missile);
	virtual bool init();
};


#endif