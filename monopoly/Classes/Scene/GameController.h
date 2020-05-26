#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "cocos2d.h"
USING_NS_CC;

class GameController : public Ref {
public:
	static GameController* createController();
	CREATE_FUNC(GameController);
	virtual bool init();
private:
	
};
#endif
