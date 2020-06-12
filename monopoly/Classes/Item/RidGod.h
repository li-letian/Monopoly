#ifndef _RIDGOD_CARD_H_
#define _RIDGOD_CARD_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class RidGod :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(RidGod);
	virtual bool init();
};

#endif