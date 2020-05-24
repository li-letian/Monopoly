#include "Character.h"
#include "Common/CommonConstant.h"

USING_NS_CC;

Character::Character()
{
	
}

Character* Character::create(int tag, const std::string& name, int money)
{
	Character* character = new Character();
	character->init(tag,name,money);
	character->autorelease();
	return character;
}

bool Character::init(int tag, const std::string& name, int money)
{
	if (!Sprite::init())
	{
		return false;
	}
	this->setTag(tag);
	name_ = name;
	money_ = money;
	is_my_turn_ = true;
	stop_times_ = 0;
	//δ��
	return true;
}

void Character::initAnimate()
{
	auto frameCache = SpriteFrameCache::getInstance();
	switch (this->getTag())
	{
	case miku:
		frameCache->addSpriteFramesWithFile("miku.plist", "miku.png");
		break;
	//�ڴ˺��¼����ɫ

	}

	Vector<SpriteFrame*>character_anim_down_vec;
	Vector<SpriteFrame*>character_anim_left_vec;
	Vector<SpriteFrame*>character_anim_right_vec;
	Vector<SpriteFrame*>character_anim_up_vec;
	for (int i = 0; i < 4; ++i)
	{
		auto frame = frameCache->getSpriteFrameByName(StringUtils::format("miku-%d.png", i));
		character_anim_down_vec.pushBack(frame);
	}
	for (int i = 4; i < 8; ++i)
	{
		auto frame = frameCache->getSpriteFrameByName(StringUtils::format("miku-%d.png", i));
		character_anim_left_vec.pushBack(frame);
	}
	for (int i = 4; i < 8; ++i)
	{
		auto frame = frameCache->getSpriteFrameByName(StringUtils::format("miku-%d.png", i));
		character_anim_right_vec.pushBack(frame);
	}
	for (int i = 4; i < 8; ++i)
	{
		auto frame = frameCache->getSpriteFrameByName(StringUtils::format("miku-%d.png", i));
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
