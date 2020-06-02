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
	std::string name_;
	Character* owner_ = nullptr;
	Business *building_=nullptr;
	int type = 0;
	int sell_value_ = business_land_value;

public:
	virtual bool onLand(Character* standing) override;
	virtual bool promote();
	virtual bool demote();
	static Business* create(MapScene* map_scene, int index);
};

#endif // !_HOTEL_H_
