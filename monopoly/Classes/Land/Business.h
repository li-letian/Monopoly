#ifndef _BUSINESS_H_
#define _BUSINESS_H_

#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Character/Character.h"

#include<string>

USING_NS_CC;

class Business : public Land {
protected:
	Character* owner_ = nullptr;
	Sprite* color_ = nullptr;
	Sprite* color_larger_ = nullptr;
	int index_larger_ = 0;
	int type_ = land_business;
	int sell_value_ = business_land_value;
	int rent_value_ = business_rent_value;

public:
	virtual bool onLand(Character* standing) override;
	bool onBusinessLand(Character* standing);
	bool promote(bool house_change = false);
	bool demote();
	static Business* create( int index);
};

#endif // !_BUSINESS_H_
