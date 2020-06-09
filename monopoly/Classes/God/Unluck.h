#ifndef _UNLUCK_H_
#define _UNLUCK_H_

#include "cocos2d.h"
class God;
class Unluck :public God {
public:
	Unluck();
	CREATE_FUNC(Unluck);
	virtual bool init();

	virtual bool onLand(Character* standing);
};
#endif