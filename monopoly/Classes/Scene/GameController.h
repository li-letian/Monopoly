#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "cocos2d.h"
#include "Character/Character.h"
#include "Scene/MapScene.h"
USING_NS_CC;

class GameController : public Ref {
public:
	GameController();
	
	CREATE_FUNC(GameController);
	virtual bool init();
private:
	void addCharacter(const std::string& name, int tag, int money,Vec2 start_pos);
	void returnToCharacter(Character*);
	void addGoButton();

	MapScene* map_scene_;
	Vector<Character*>characters_;
	int whose_turn_;	//记录轮到第几个角色行动
};
#endif
