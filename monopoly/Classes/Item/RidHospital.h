#ifndef _RID_HOSPITAL_H_
#define _RID_HOSPITAL_H_

class Character;
#include "Item.h"
#include "Common/CommonMethod.h"
class RidHospital :public Item {
public:
	virtual void worked(Character* player);
	CREATE_FUNC(RidHospital);
	virtual bool init();
};

#endif