#ifndef _SLEEP_H_
#define _SLEEP_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class HolidayCard :public Item {
public:
	virtual void work(Character* player);
	CREATE_FUNC(HolidayCard);
	virtual bool init();
private:
	std::string name_ = std::string("");
	std::string content_ = std::string("");
};

#endif