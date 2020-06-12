#ifndef _ANGEL_H_
#define _ANGEL_H_

#include "cocos2d.h"
#include "God.h"


class Character;
class Angel :public God {
public:
	Angel();
	CREATE_FUNC(Angel);

	virtual bool init();
	static void popUpDialog();
};
#endif // !_ANGEL_H_
