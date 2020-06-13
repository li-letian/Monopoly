#ifndef _IMPUTE_H_
#define _IMPUTE_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Impute :public Item {
public:
	virtual void worked(Character* player);
	CREATE_FUNC(Impute);
	virtual bool init();
};

#endif