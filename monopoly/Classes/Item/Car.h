#ifndef _CAR_H_
#define _CAR_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Car :public Item {
public:
	virtual void work(Character* player);

	static Car* Car::create();
	virtual std::string getItemName();
	virtual std::string getContent();
private:
	std::string name_ = std::string("����Ь");
	std::string content_ = std::string("����ͣ����������");
};

#endif