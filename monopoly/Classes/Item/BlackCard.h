#ifndef _BLACK_CARD_H_
#define _BLACK_CARD_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class BlackCard :public Item {
public:
	virtual void work(Character* player);

	static BlackCard* BlackCard::create();
	virtual std::string getItemName();
	virtual std::string getContent();
private:
	std::string name_ = std::string("�ڿ�");
	std::string content_ = std::string("���е������ֿ��Ӷ�û��T T");
};

#endif