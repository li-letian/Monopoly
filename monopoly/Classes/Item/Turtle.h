#ifndef _TURTLE_H_
#define _TURTLE_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Turtle :public Item {
public:
	virtual void work(Character* player);

	static Turtle* Turtle::create();
	virtual std::string getItemName();
	virtual std::string getContent();
private:
	std::string name_ = std::string("乌龟卡");
	std::string content_ = std::string("只走一步，可能会有额外惊喜哦！");
};

#endif