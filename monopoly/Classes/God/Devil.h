#ifndef _DEVIL_H_
#define _DEVIL_H_

#include "cocos2d.h"

class God;
class Devil :public God {
public:
	Devil();
	CREATE_FUNC(Devil);
	virtual bool init();

	virtual bool onLand(Character* standing);
};
#endif