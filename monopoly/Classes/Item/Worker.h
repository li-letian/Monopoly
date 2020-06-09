#ifndef _WORKER_H_
#define _WORKER_H_

#include "Item/Item.h"
#include "cocos2d.h"
USING_NS_CC;
class Character;
class Worker : public Item {	//µÀ¾ßÃû³Æ
public:
	virtual void work(Character* player);
	CREATE_FUNC(Worker);
	virtual bool init();
};


#endif