#include "Character/Character.h"
#include "Common/CommonConstant.h"

USING_NS_CC;

Character::Character()
	:character_anim_down_(nullptr),
	character_anim_left_(nullptr),
	character_anim_right_(nullptr),
	character_anim_up_(nullptr),
	character_frame_cache_(nullptr),
	name_(),
	money_(15000),
	stop_times_(0),
	cur_pos_(0),
	steps_scope_(walk_steps)
{
	this->setTag(0);
}

Character::~Character()
{
	//�ͷ���ǰretain�Ķ�������
	character_anim_down_->release();
	character_anim_left_->release();
	character_anim_right_->release();
	character_anim_up_->release();
}


bool Character::init(const std::string& name, int tag, int money, int cur_pos)
{
	if (!Sprite::init())
	{
		return false;
	}

	//����һЩ��������
	name_ = name;
	this->setTag(tag);
	money_ = money;
	cur_pos_ = cur_pos;

	initAnimate();	//��ʼ����������
	initSprite();	//���������ʼ����
	
	return true;
}

void Character::initAnimate()
{
	character_frame_cache_ = SpriteFrameCache::getInstance();
	character_frame_cache_->addSpriteFramesWithFile(StringUtils::format("%s.plist", name_.c_str()), StringUtils::format("%s.png", name_.c_str()));

	Vector<SpriteFrame*>character_anim_down_vec;
	Vector<SpriteFrame*>character_anim_left_vec;
	Vector<SpriteFrame*>character_anim_right_vec;
	Vector<SpriteFrame*>character_anim_up_vec;

	for (int i = 0; i < 4; ++i)
	{
		auto frame = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-%d.png", name_.c_str(), i));
		character_anim_down_vec.pushBack(frame);
	}
	for (int i = 4; i < 8; ++i)
	{
		auto frame = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-%d.png", name_.c_str(), i));
		character_anim_left_vec.pushBack(frame);
	}
	for (int i = 8; i < 12; ++i)
	{
		auto frame = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-%d.png", name_.c_str(), i));
		character_anim_right_vec.pushBack(frame);
	}
	for (int i = 12; i < 16; ++i)
	{
		auto frame = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-%d.png", name_.c_str(), i));
		character_anim_up_vec.pushBack(frame);
	}
	
	character_anim_down_ = Animate::create(Animation::createWithSpriteFrames(character_anim_down_vec, character_walk_delay_time));
	character_anim_left_ = Animate::create(Animation::createWithSpriteFrames(character_anim_left_vec, character_walk_delay_time));
	character_anim_right_ = Animate::create(Animation::createWithSpriteFrames(character_anim_right_vec, character_walk_delay_time));
	character_anim_up_ = Animate::create(Animation::createWithSpriteFrames(character_anim_up_vec, character_walk_delay_time));

	//��ʱ����ӵ����ڵ��У�retain�Է�ֹ��autorelease
	character_anim_down_->retain();
	character_anim_left_->retain();
	character_anim_right_->retain();
	character_anim_up_->retain();
}

void Character::initSprite()
{
	auto spf = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-4.png", name_.c_str()));
	this->initWithSpriteFrame(spf);
	this->setAnchorPoint(Vec2(0.5f, 0.2f));
}

