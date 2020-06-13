#ifndef _MINE_H_
#define _MINE_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Mine :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(Mine);
	virtual bool init();
};

#endif