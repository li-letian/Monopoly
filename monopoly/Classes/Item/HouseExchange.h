#ifndef _HOUSE_EXCHANGE_H_
#define _HOUSE_EXCHANGE_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class HouseExchange :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(HouseExchange);
	virtual bool init();
};

#endif