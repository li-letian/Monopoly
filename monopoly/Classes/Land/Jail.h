#ifndef _JAIL_H_
#define _JAIL_H_

#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"

#include<string>

USING_NS_CC;

class Jail : public Land {
protected:
	std::string name_;

public:
	virtual bool onLand(Character* standing) override;
	static Jail* create(int index);
	
};

#endif // !_JAIL_H_
