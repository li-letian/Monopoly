#ifndef _HOUSE_CHANGE_H_
#define _HOUSE_CHANGE_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class HouseChange :public Item {
public:
	virtual void work(Character* player);

	static HouseChange* HouseChange::create();
	virtual std::string getItemName();
	virtual std::string getContent();
private:
	std::string name_ = std::string("购地证明");
	std::string content_ = std::string("这块土地和我有缘，归我了！");
};

#endif