#ifndef _TURN_AROUND_H_
#define _TURN_AROUND_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class TurnAround :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(TurnAround);
	virtual bool init();
};

#endif