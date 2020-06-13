#ifndef _DEVIL_CARD_H_
#define _DEVIL_CARD_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class DevilCard :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(DevilCard);
	virtual bool init();
};

#endif