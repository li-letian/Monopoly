#ifndef _RED_CARD_H_
#define _RED_CARD_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class RedCard :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(RedCard);
	virtual bool init();
};

#endif