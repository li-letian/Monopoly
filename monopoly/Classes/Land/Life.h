#ifndef _LIFE_H_
#define _LIFE_H_

#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"

#include<string>

USING_NS_CC;

class Life : public Land {
protected:
	std::string name_;

public:
	virtual bool onLand(Character* standing) override;
	static Life* create(int index);

};

#endif // !_LIFE_H_
