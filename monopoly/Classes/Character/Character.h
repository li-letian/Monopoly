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
	MapScene* map_scene_ = nullptr;
	CC_SYNTHESIZE(std::string, name_, PlayerName);	//����
protected:
	int money_=0;//��Ǯ
	int deposit_=0;//���
	int loan_=0;//����
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
	CC_SYNTHESIZE(int, cur_pos_, CurPos);			//��ǰ����λ��
	CC_SYNTHESIZE(int, steps_scope_, StepsScope);	//һ�ο��ߵĸ�����Χ

	CC_SYNTHESIZE(int, stop_times_, StopTimes);		//ֹͣʱ�䣨������ҽԺ���������ȼ�)
	CC_SYNTHESIZE(int, condition_, Condition);		//����״̬������Ϊ��ҽԺ���ڼ������ڶȼ٣�
	CC_SYNTHESIZE(int, insurance_times, Insurance);
	CC_SYNTHESIZE(int, estate_value_, EstateValue);	//�ز���ֵ
	CC_SYNTHESIZE(int, gain_value_, GainValue);		//�ϴν�������˰������ü�ֵ
	CC_SYNTHESIZE(int, god_possessed_, GodPossessed);//��¼��ʲô���鸽��
	CC_SYNTHESIZE(int, god_times_, GodTimes);		//��¼���ɵ�ʣ�����ʱ��
	CC_SYNTHESIZE(int, turtle_times_, TurtleTimes);	//��¼�ڹ��ʣ�����
	CC_SYNTHESIZE(int, control_dice_point_, ControlDicePoint);//��¼ң�����ӵĵ���
	CC_SYNTHESIZE(bool, is_stay_, IsStay);			//��¼�Ƿ�ʹ��ͣ����
	CC_SYNTHESIZE(int, toward_direction_, TowardDirection);//���ﳯ��ǰ���
};


#endif // !_CHARACTER_H_
