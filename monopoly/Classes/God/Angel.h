#ifndef _ANGEL_H_
#define _ANGEL_H_

#include "cocos2d.h"

class God;
class Angel :public God {
public:
	Angel();
	CREATE_FUNC(Angel);
	virtual bool init();

	virtual bool onLand(Character* standing);
};
#endif // !_ANGEL_H_
