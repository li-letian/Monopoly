#ifndef _RISE_PRICE_H_
#define _RISE_PRICE_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class RisePrice :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(RisePrice);
	virtual bool init();
};

#endif