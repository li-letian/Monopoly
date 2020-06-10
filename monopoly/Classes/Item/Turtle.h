#ifndef _TURTLE_H_
#define _TURTLE_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Turtle :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(Turtle);
	virtual bool init();
};

#endif