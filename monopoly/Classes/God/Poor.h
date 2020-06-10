#ifndef _POOR_H_
#define _POOR_H_

#include "cocos2d.h"
#include "God.h"
class Character;
class Poor :public God {
public:
	Poor();
	CREATE_FUNC(Poor);
	virtual bool init();

	virtual bool onLand(Character* standing);
	static void popUpDialog();
};
#endif