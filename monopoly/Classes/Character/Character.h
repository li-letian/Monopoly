#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "cocos2d.h"

USING_NS_CC;

class Character : public Sprite {
public:
	Character();
	~Character() = default;
	
	//这里没使用一般的CREATE_FUNC宏与virtual init的组合
	//主要是为了给init增加参数，方便调整初始值，其余效果一致
	static Character* create(int tag, const std::string& name, int money = 15000);
	bool init(int tag, const std::string& name, int money);

	//4个动画对象，分别存储人物向下、左、右、上移动的动画
	CC_SYNTHESIZE(Animate*, character_anim_down_, CharacterAnimDown);
	CC_SYNTHESIZE(Animate*, character_anim_left_, CharacterAnimLeft);
	CC_SYNTHESIZE(Animate*, character_anim_right_, CharacterAnimRight);
	CC_SYNTHESIZE(Animate*, character_anim_up_, CharacterAnimUp);

	void initAnimate();		//初始化动画对象
private:
	//角色属性
	CC_SYNTHESIZE(std::string, name_, PlayerName);	//名字
	CC_SYNTHESIZE(int, money_, Money);				//金钱
	CC_SYNTHESIZE(bool, is_my_turn_, IsMyTurn);	    //角色本回合是否已经行动
	CC_SYNTHESIZE(int, stop_times_, StopTimes);		//停止时间（可能在医院、监狱、度假）
};

#endif // !_CHARACTER_H_
