#ifndef _AVERAGE_CARD_H_
#define _AVERAGE_CARD_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Average :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(Average);
	virtual bool init();
};

#endif