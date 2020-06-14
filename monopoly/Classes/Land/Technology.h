#ifndef _TECHNOLOGY_H_
#define _TECHNOLOGY_H_

#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonMethod.h"
#include "Scene/StockScene.h"

#include<string>

USING_NS_CC;

class Technology : public Land {
protected:

public:
	virtual bool onLand(Character* standing) override;
	static Technology* create(int index);

};

#endif // !_TECHNOLOGY_H_
