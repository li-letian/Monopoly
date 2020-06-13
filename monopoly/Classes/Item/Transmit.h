#ifndef _TRANSMIT_H_
#define _TRANSMIT_H_

#include "Item/Item.h"
#include "cocos2d.h"

class Character;
class Transmit : public Item {	//µÀ¾ßÃû³Æ
public:
	virtual void work(Character* player);
	CREATE_FUNC(Transmit);
	virtual bool init();
	void workOnGod();
	void workOnCharacter(Character* user,Character* character);
};


#endif