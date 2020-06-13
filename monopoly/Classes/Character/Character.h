#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "cocos2d.h"
#include "Scene/MapScene.h"

USING_NS_CC;

class MapScene;
class Character : public Sprite {
public:
	Character();
	~Character();
	
	static Character* create(const std::string& name, int tag, int money, int cur_pos,MapScene* map_scene)
	{
		auto pRet = new(std::nothrow) Character();
		if (pRet && pRet->init(name, tag, money, cur_pos))
		{
			pRet->map_scene_ = map_scene;
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	}

	bool init(const std::string& name, int tag, int money, int cur_pos);

	//4个动画对象，分别存储人物向下、左、右、上移动的动画
	CC_SYNTHESIZE(Animate*, character_anim_down_, CharacterAnimDown);
	CC_SYNTHESIZE(Animate*, character_anim_left_, CharacterAnimLeft);
	CC_SYNTHESIZE(Animate*, character_anim_right_, CharacterAnimRight);
	CC_SYNTHESIZE(Animate*, character_anim_up_, CharacterAnimUp);
	CC_SYNTHESIZE(SpriteFrameCache*, character_frame_cache_, FrameCache);

	void initSprite();		//初始化人物形象
	void initAnimate();		//初始化动画对象
	

private:
	//角色属性
	MapScene* map_scene_ = nullptr;
	CC_SYNTHESIZE(std::string, name_, PlayerName);	//名字
protected:
	int money_=0;//金钱
	int deposit_=0;//存款
	int loan_=0;//贷款
public:
	int getMoney()const
	{
		return money_;
	}
	int getDeposit()const
	{
		return deposit_;
	}
	int getLoan()
	{
		return loan_;
	}
	void setMoney(int money)
	{
		money_ = money;
		map_scene_->updateInformation(this);
	}
	void setDeposit(int deposit)
	{
		deposit_ = deposit;
		map_scene_->updateInformation(this);
	}
	void setLoan(int loan)
	{
		loan_ = loan;
		map_scene_->updateInformation(this);
	}
	CC_SYNTHESIZE(int, cur_pos_, CurPos);			//当前所处位置
	CC_SYNTHESIZE(int, steps_scope_, StepsScope);	//一次可走的格数范围

	CC_SYNTHESIZE(int, stop_times_, StopTimes);		//停止时间（可能在医院、监狱、度假)
	CC_SYNTHESIZE(int, condition_, Condition);		//人物状态（可能为在医院、在监狱、在度假）
	CC_SYNTHESIZE(int, insurance_times, Insurance);
	CC_SYNTHESIZE(int, estate_value_, EstateValue);	//地产价值
	CC_SYNTHESIZE(int, gain_value_, GainValue);		//上次缴纳所得税起的所得价值
	CC_SYNTHESIZE(int, god_possessed_, GodPossessed);//记录被什么神灵附身
	CC_SYNTHESIZE(int, god_times_, GodTimes);		//记录神仙的剩余持续时间
	CC_SYNTHESIZE(int, turtle_times_, TurtleTimes);	//记录乌龟的剩余次数
	CC_SYNTHESIZE(int, control_dice_point_, ControlDicePoint);//记录遥控骰子的点数
	CC_SYNTHESIZE(bool, is_stay_, IsStay);			//记录是否被使用停留卡
	CC_SYNTHESIZE(int, toward_direction_, TowardDirection);//人物朝向（前或后）
};


#endif // !_CHARACTER_H_
