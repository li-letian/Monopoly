#ifndef _HOUSE_DESTORY_H_
#define _HOUSE_DESTORY_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class HouseDestory :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(HouseDestory);
	virtual bool init();
};

#endif