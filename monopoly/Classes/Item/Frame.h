#ifndef _FRAME_H_
#define _FRAME_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Frame:public Item{
public:
	virtual void work(Character* player);
	std::string name_ = std::string("¥Ú«Æ");
	static Frame* Frame::create_();
	virtual std::string getItemName();
};

#endif