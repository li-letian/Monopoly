#include "Character.h"
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
	//Î´Íê
	return true;
}
