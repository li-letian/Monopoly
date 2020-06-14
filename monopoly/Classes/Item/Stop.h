#ifndef _STOP_H_
#define _STOP_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Stop :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(Stop);
	virtual bool init();
};

#endif