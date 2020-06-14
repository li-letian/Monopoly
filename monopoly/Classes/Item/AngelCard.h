#ifndef _ANGEL_CARD_H_
#define _ANGEL_CARD_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class AngelCard :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(AngelCard);
	virtual bool init();
};

#endif