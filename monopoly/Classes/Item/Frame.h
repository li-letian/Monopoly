#ifndef _FRAME_H_
#define _FRAME_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Frame:public Item{
public:
	virtual void work(Character* player);
	
	static Frame* Frame::create();
	virtual std::string getItemName();
	virtual std::string getContent();
private:
    std::string name_ = std::string("打钱");
	std::string content_ = std::string("不需要操作");
};

#endif