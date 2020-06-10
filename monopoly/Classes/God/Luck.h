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

	virtual bool onLand(Character* standing);
};
#endif // ! _LUCK_H_
