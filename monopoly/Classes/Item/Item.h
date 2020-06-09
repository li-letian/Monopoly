#ifndef _ITEM_H_
#define _ITEM_H_
#include "cocos2d.h"
#include "Character/Character.h"

USING_NS_CC;

class Item : public Sprite {
protected:
	//道具名称
	std::string name_;
	std::string content_;

public:
	virtual void work(Character* player)
	{
		return;
	}
	virtual std::string getItemName()
	{
		return name_;
	}
	virtual std::string getContent()
	{
		return content_;
	}
	virtual bool init()
	{
		if (!Sprite::init())
			return false;
		return true;
	}
};

#endif