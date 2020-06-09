#ifndef _HOSPITAL_H_
#define _HOSPITAL_H_

#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"

#include<string>

USING_NS_CC;

class Hospital : public Land {
protected:
public:
	virtual bool onLand(Character* standing) override;
	static Hospital* create(int index);

};

#endif // !_HOSPITAL_H_
