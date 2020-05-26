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

	//4���������󣬷ֱ�洢�������¡����ҡ����ƶ��Ķ���
	CC_SYNTHESIZE(Animate*, character_anim_down_, CharacterAnimDown);
	CC_SYNTHESIZE(Animate*, character_anim_left_, CharacterAnimLeft);
	CC_SYNTHESIZE(Animate*, character_anim_right_, CharacterAnimRight);
	CC_SYNTHESIZE(Animate*, character_anim_up_, CharacterAnimUp);
	CC_SYNTHESIZE(SpriteFrameCache*, character_frame_cache_, FrameCache);

	void initSprite();		//��ʼ����������
	void initAnimate();		//��ʼ����������
private:
	//��ɫ����
	CC_SYNTHESIZE(std::string, name_, PlayerName);	//����
	CC_SYNTHESIZE(int, money_, Money);				//��Ǯ
	CC_SYNTHESIZE(bool, is_my_turn_, IsMyTurn);	    //��ɫ���غ��Ƿ��Ѿ��ж�
	CC_SYNTHESIZE(int, stop_times_, StopTimes);		//ֹͣʱ�䣨������ҽԺ���������ȼ�)
	CC_SYNTHESIZE(Vec2, cur_pos_, CurPos);		//��ǰ����λ��
};

#endif // !_CHARACTER_H_
