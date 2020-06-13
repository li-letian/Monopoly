#ifndef _BLACK_CARD_H_
#define _BLACK_CARD_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class BlackCard :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(BlackCard);
	virtual bool init();
};

#endif