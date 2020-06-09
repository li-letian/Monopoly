#ifndef _CONTROL_DICE_H_
#define _CONTROL_DICE_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class ControlDice :public Item {
public:
	virtual void work(Character* player);

	static ControlDice* ControlDice::create();
	virtual std::string getItemName();
	virtual std::string getContent();
private:
	std::string name_ = std::string("ң������");
	std::string content_ = std::string("�����ƶ�����");
};

#endif