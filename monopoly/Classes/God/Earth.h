#ifndef _EARTH_H_
#define _EARTH_H_

#include "cocos2d.h"

class God;
class Earth : public God {
public:
	Earth();
	CREATE_FUNC(Earth);
	virtual bool init();

	virtual bool onLand(Character* standing);
protected:
};

#endif