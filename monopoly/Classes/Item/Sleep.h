#ifndef _SLEEP_H_
#define _SLEEP_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Sleep :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(Sleep);
	virtual bool init();
};

#endif