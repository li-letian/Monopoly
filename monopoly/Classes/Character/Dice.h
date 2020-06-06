#ifndef _DICE_H_
#define _DICE_H_

#include "cocos2d.h"
#include "Common/CommonMethod.h"
USING_NS_CC;
class Dice : public Ref {
public:
	CREATE_FUNC(Dice);
	virtual bool init();

	int RollTheDice(int steps_scope);		//ÖÀÒ»´Î÷»×Ó
	static int getARandomNumber(int scope);
};

#endif