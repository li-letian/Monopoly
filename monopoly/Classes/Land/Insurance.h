#ifndef _INSURANCE_H_
#define _INSURANCE_H_

#include "cocos2d.h"
#include "Land.h"

#include<string>

USING_NS_CC;
class Character;
class Insurance : public Land {
protected:

public:
	virtual bool onLand(Character* standing) override;
	static Insurance* create(int index);

};

#endif // !_INSURANCE_H_
