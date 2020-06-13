#ifndef _FRAME_CARD_H_
#define _FRAME_CARD_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Frame :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(Frame);
	virtual bool init();
};

#endif