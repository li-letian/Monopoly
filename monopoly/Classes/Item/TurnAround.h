#ifndef _TURN_AROUND_H_
#define _TURN_AROUND_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class TurnAround :public Item {
public:
	virtual void work(Character* player);

	static TurnAround* TurnAround::create();
	virtual std::string getItemName();
	virtual std::string getContent();
private:
	std::string name_ = std::string("ת��");
	std::string content_ = std::string("��Ȼ����");
};

#endif