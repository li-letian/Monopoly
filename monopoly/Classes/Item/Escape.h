#ifndef _ESCAPE_H_
#define _ESCAPE_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Escape :public Item {
public:
	virtual void worked(Character* player);
	CREATE_FUNC(Escape);
	virtual bool init();
};

#endif