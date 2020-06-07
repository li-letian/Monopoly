#ifndef _OIL_H_
#define _OIL_H_

#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonMethod.h"
#include "Scene/StockScene.h"

#include<string>

USING_NS_CC;

class Oil : public Land {
protected:
	std::string name_;

public:
	virtual bool onLand(Character* standing) override;
	static Oil* create(int index);

};

#endif // !_OIL_H_
