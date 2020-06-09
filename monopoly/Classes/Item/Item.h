#ifndef _ITEM_H_
#define _ITEM_H_


#include "cocos2d.h"
USING_NS_CC;
class Character;
class Item : public Sprite {
private:
	//CC_SYNTHESIZE(std::string, name_, ItemName);	//道具名称
	std::string name_;
public:
	virtual void work(Character* player)=0;
	virtual std::string getItemName()=0;
};









#endif