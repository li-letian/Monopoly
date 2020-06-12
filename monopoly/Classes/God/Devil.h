#ifndef _DEVIL_H_
#define _DEVIL_H_

#include "cocos2d.h"
#include "God.h"


class Character;
class Devil :public God {
public:
	Devil();
	CREATE_FUNC(Devil);

	virtual bool init();
	static void popUpDialog();
};
#endif