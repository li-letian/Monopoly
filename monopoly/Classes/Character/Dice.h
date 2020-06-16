#ifndef _DICE_H_
#define _DICE_H_

#include "cocos2d.h"

USING_NS_CC;
class Character;
class Dice : public Node {
public:
	CREATE_FUNC(Dice);
	virtual bool init();

	void RollTheDice(int steps_scope,Character*character);		//ÖÀÒ»´Î÷»×Ó
	static int getARandomNumber(int scope);
	void decreaseNumber();
private:
	void increaseNumber();
	void endAppear();
	void showCurNumber();
	int cur_point_ = 0;
	int steps_ = 0;
	float dice_change_time_ = 0;
};

#endif