#ifndef _CONTROL_DICE_H_
#define _CONTROL_DICE_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class ControlDice :public Item {
public:
public:
	virtual void work(Character* player);
	CREATE_FUNC(ControlDice);
	virtual bool init();
};

#endif