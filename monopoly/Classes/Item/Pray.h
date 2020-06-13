#ifndef _PRAY_CARD_H_
#define _PRAY_CARD_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Pray :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(Pray);
	virtual bool init();
};

#endif