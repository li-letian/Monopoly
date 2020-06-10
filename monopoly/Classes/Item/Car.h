#ifndef _CAR_H_
#define _CAR_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Car :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(Car);
	virtual bool init();
};

#endif