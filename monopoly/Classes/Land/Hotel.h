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
	Character* owner_= nullptr;
	Sprite* color_ = nullptr;
	int rank_=0;
	int sell_value_ = 0;
	int rent_value_ = 0;
	float rent_rise_ = 1.f;
	float sell_rise_ = 1.f;

public:
	friend class Hotel;
	virtual bool onLand(Character* standing) override;
	bool promote();
	bool demote();
	static Hotel* create(int index);
	bool setRentRise(float rise_rate);
	float getRentRise()const;
	bool setSellRise(float rise_rate);
	float getSellRise()const;
	int getRank()const;
	Character* getOwner()const;
	bool setOwner(Character* character);	//character可为空,代表旅馆再次无主
	int getValue()const;
};

#endif // !_HOTEL_H_
