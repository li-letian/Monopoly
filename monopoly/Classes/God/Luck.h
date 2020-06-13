#ifndef _LUCK_H_
#define _LUCK_H_

#include "cocos2d.h"
#include "God.h"

class Character;
class Luck :public God {
public:
	Luck();
	CREATE_FUNC(Luck);

	virtual bool init();
	static void Luck::popUpDialog();
};
#endif // ! _LUCK_H_
