#ifndef _BANK_H_
#define _BANK_H_

#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonMethod.h"

#include<string>

USING_NS_CC;

class Bank : public Land {
protected:
	std::string name_;

public:
	virtual bool onLand(Character* standing) override;
	virtual bool byLand(Character* standing) override;
	static Bank* create(MapScene* map_scene, int index);

};

#endif // !_BANK_H_
