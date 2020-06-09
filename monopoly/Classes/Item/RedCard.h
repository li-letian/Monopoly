#ifndef _RED_CARD_H_
#define _RED_CARD_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class RedCard :public Item {
public:
	virtual void work(Character* player);

	static RedCard* RedCard::create();
	virtual std::string getItemName();
	virtual std::string getContent();
private:
	std::string name_ = std::string("ºì¿¨");
	std::string content_ = std::string("¹É¼Û±©ÕÇ");
};

#endif