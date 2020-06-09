#ifndef _POOR_H_
#define _POOR_H_

#include "cocos2d.h"
class God;
class Poor :public God {
public:
	Poor();
	CREATE_FUNC(Poor);
	virtual bool init();

	virtual bool onLand(Character* standing);
};
#endif