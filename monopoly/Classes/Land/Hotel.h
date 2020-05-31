#ifndef _HOTEL_H_
#define _HOTEL_H_

#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"

#include<string>

USING_NS_CC;

class Hotel : public Land {
protected:
	std::string name_;
	Character* owner_= nullptr;
	int rank_=0;
	int sell_value_ = 0;
	int rent_value_ = 0;
	float rent_rise_ = 1.f;

public:
	virtual bool onLand(Character* standing) override;
	virtual bool promote() override;
	virtual bool demote()override;
	static Hotel* create(MapScene * map_scene,int index);
};

#endif // !_HOTEL_H_
