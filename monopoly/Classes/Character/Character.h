#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "cocos2d.h"

USING_NS_CC;

class Character : public Sprite {
public:
	Character();
	~Character();
	
	static Character* create(const std::string& name, int tag, int money);
	bool init(const std::string& name, int tag, int money);

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
	CC_SYNTHESIZE(std::string, name_, PlayerName);	//名字
	CC_SYNTHESIZE(int, money_, Money);				//金钱
	CC_SYNTHESIZE(bool, is_my_turn_, IsMyTurn);	    //角色本回合是否已经行动
	CC_SYNTHESIZE(int, stop_times_, StopTimes);		//停止时间（可能在医院、监狱、度假)
	CC_SYNTHESIZE(Vec2, cur_pos_, CurPos);		//当前所处位置
};

#endif // !_CHARACTER_H_
