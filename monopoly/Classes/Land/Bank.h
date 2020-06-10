#ifndef _BANK_H_
#define _BANK_H_

#include "cocos2d.h"
#include "Land.h"

#include<string>

USING_NS_CC;
class Character;
class Bank : public Land {
protected:

public:
	virtual bool onLand(Character* standing) override;
	virtual bool byLand(Character* standing) override;
	static Bank* create(int index);

};

#endif // !_BANK_H_
