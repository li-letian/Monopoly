#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Character/Character.h"
#include "God/God.h"
USING_NS_CC;

class God;
class MapScene;
class Dice;
class StockScene;
class ItemScene;
class GameController : public Node
{
public:
	static GameController* create(std::vector<bool>is_ai);
	bool init(std::vector<bool>is_ai);

	void addGoButton();							//添加go按钮
	void returnToCharacter(Character *);		//回到角色视角
	void startRealGo(int steps_to_go);			//指定当前角色真正开始走
	int judgeDirection(int cur_pos);			//判断要走的方向
	void moveOneStep(int direction);			//指定当前角色按某方向走一格
	void endGo();								//在一步结束后判断要执行什么动作
	void dealWithGod();							//行走结束后处理God
	void dealWithLand();						//行走结束后处理Land
	void backToStand(Character* character);		//使指定角色回到正确的站立朝向
	void updateGod(int god_type);				//更新神仙在地图上的位置

	Vector<Character*>& getCharacters()
	{
		return characters_;
	}
	Vector<God*>& getGods()
	{
		return gods_;
	}
	Character* getCurCharacter()const
	{
		return characters_.at(whose_turn_);
	}

private:
	void music_open();								 //打开bgm
	void music_close();								 //关闭bgm
	void addEventListenerCustom();					 //添加自定义事件监听器
	//添加角色
	void addCharacter(const std::string& name, int tag, int money, int start_pos, bool is_ai);
	void initGod();									 //初始化游戏的神
	void ReadyToStartGo();							 //指定当前角色准备开始走

	EventListenerTouchOneByOne* listener_block_ = nullptr;
	Dice* dice_ = nullptr;							 //储存本局游戏的随机数
	MapScene* map_scene_ = nullptr;					 //储存地图场景
	Vector<Character*>characters_;					 //储存本局游戏所有角色的Vector
	Vector<God*>gods_;								 //储存本局游戏所有神的Vector

	EventListenerCustom *listener_custom_ = nullptr; //自定义事件分发器
	StockScene* stock_layer_=nullptr;                //储存股市场景
	ItemScene* item_layer_ = nullptr;                //储存道具场景
	int whose_turn_=0;								 //记录轮到第几个角色行动
	int steps_to_go_=0;								 //记录本轮要走几步
	int steps_has_gone_=0;							 //记录本轮已走几步
};
#endif
