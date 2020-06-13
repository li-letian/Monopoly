#ifndef _HOUSE_CHANGE_H_
#define _HOUSE_CHANGE_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class HouseChange :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(HouseChange);
	virtual bool init();
};

#endif