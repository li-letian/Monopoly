#ifndef _HOTEL_H_
#define _HOTEL_H_

#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonMethod.h"

#include<string>

USING_NS_CC;

class Hotel : public Land {
protected:
	std::string name;


public:
	virtual bool onLand();

	static Hotel* create()
	{
		auto pRet = new(std::nothrow) Hotel();
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	}


private:

};

#endif // !_HOTEL_H_
