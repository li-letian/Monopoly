#ifndef _RICH_H_
#define _RICH_H_

#include "cocos2d.h"
class God;
class Rich :public God {
public:
	Rich();
	CREATE_FUNC(Rich);
	virtual bool init();

	virtual bool onLand(Character* standing);
};
#endif