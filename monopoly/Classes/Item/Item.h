#ifndef _ITEM_H_
#define _ITEM_H_


#include "cocos2d.h"
USING_NS_CC;
class Character;
class Item : public Sprite {
private:
	CC_SYNTHESIZE(std::string, name_, ItemName);	//Ãû×Ö
public:
	virtual void work(Character* player) = 0;

};









#endif