#ifndef _REVENGE_H_
#define _REVENGE_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Revenge :public Item {
public:
	virtual void worked(Character* player);
	CREATE_FUNC(Revenge);
	virtual bool init();
};

#endif