#ifndef _RID_JAIL_H_
#define _RID_JAIL_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class RidJail :public Item {
public:
	virtual void worked(Character* player);
	CREATE_FUNC(RidJail);
	virtual bool init();
};

#endif