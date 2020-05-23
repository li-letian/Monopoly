#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "cocos2d.h"
USING_NS_CC;

class GameController : public Layer {
public:
	CREATE_FUNC(GameController);
	virtual bool init();

	static GameController* game_controller_instance_;
	static GameController* getInstance();
private:
	
};
#endif
