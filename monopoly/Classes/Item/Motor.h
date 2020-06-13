#ifndef _MOTOR_H_
#define _MOTOR_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Motor :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(Motor);
	virtual bool init();
};

#endif