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
	std::string name_ = std::string("�ȼٿ�");
	std::string content_ = std::string("������ô������ȥ����");
};

#endif