#ifndef _SLEEP_H_
#define _SLEEP_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class HolidayCard :public Item {
public:
	virtual void work(Character* player);

	static HolidayCard* HolidayCard::create();
	virtual std::string getItemName();
	virtual std::string getContent();
private:
	std::string name_ = std::string("度假卡");
	std::string content_ = std::string("世界这么大，我想去看看");
};

#endif