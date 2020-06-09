#ifndef _MOTOR_H_
#define _MOTOR_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class Motor :public Item {
public:
	virtual void work(Character* player);

	static Motor* Motor::create();
	virtual std::string getItemName();
	virtual std::string getContent();
private:
	std::string name_ = std::string("Զ��Ь");
	std::string content_ = std::string("��һ��ĸо�����");
};

#endif