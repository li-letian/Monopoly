#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "cocos2d.h"
#include "Character/Character.h"
#include "Scene/MapScene.h"
#include "Character/Dice.h"
USING_NS_CC;

class GameController : public Node {
public:
	GameController();
	~GameController();
	
	CREATE_FUNC(GameController);
	virtual bool init();
private:
	void addEventListenerCustom();			//添加自定义事件监听器
	void addCharacter(const std::string& name, int tag, int money,int start_pos);//添加角色
	void returnToCharacter(Character*);		//回到角色视角
	void addGoButton();						//添加go按钮
	void StartGo();							//指定当前角色开始走
	int JudgeDirection(int cur_pos);		//判断要走的方向
	void MoveOneStep(int direction);		//指定当前角色按某方向走一格
	void endGo();							//MoveOneStep结束前调用的函数

	Dice* dice_;							//储存本局游戏的随机数
	MapScene* map_scene_;					//储存地图场景
	std::vector<Character*>characters_;		//储存本局游戏所有角色的Vector
	EventListenerCustom* listener_custom_;  //自定义事件分发器
	Menu* go_button_menu_;					//go_button
	int whose_turn_;						//记录轮到第几个角色行动
	int steps_to_go_;						//记录本轮要走几步
	int steps_has_gone_;					//记录本轮已走几步
};
#endif
