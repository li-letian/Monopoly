#ifndef _ROBOT_H_
#define _ROBOT_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Robot :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(Robot);
	virtual bool init();
};

#endif