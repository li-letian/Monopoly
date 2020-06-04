#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "cocos2d.h"
#include "Scene/MapScene.h"
#include "Common/CommonMethod.h"
USING_NS_CC;

class Character : public Sprite {
public:
	Character();
	~Character();
	
	static Character* create(const std::string& name, int tag, int money, int cur_pos)
	{
		auto pRet = new(std::nothrow) Character();
		if (pRet && pRet->init(name, tag, money, cur_pos))
		{
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
	CC_SYNTHESIZE(std::string, name_, PlayerName);	//名字
	CC_SYNTHESIZE(int, money_, Money);				//金钱
	CC_SYNTHESIZE(int, cur_pos_, CurPos);			//当前所处位置
	CC_SYNTHESIZE(int, steps_scope_, StepsScope);	//一次可走的格数范围

	CC_SYNTHESIZE(int, stop_times_, StopTimes);		//停止时间（可能在医院、监狱、度假)
	CC_SYNTHESIZE(int, condition_, Condition);		//人物状态（可能为在医院、在监狱、在度假）

	CC_SYNTHESIZE(int, estate_value_, EstateValue);	//地产价值
	CC_SYNTHESIZE(int, gain_value_, GainValue);		//上次缴纳所得税起的所得价值
};


class Information :public Layer {
public:
	void updateInformation(Character* player);
	static Information* Information::createScene(MapScene* map_scene);
	virtual bool init();
	CREATE_FUNC(Information);
protected:
	MapScene* map_scene_= nullptr ;            //记录map场景
	int year_ = 1;
	int month_ = 1;
	int day_ = 1;
};
#endif // !_CHARACTER_H_
