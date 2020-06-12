#ifndef _MINE_POSITION_H_
#define _MINE_POSITION_H_

#include "God/God.h"

class Character;
class MinePosition :public God {
public:
	MinePosition();
	CREATE_FUNC(MinePosition);
	virtual bool init();
	virtual bool onLand(Character* standing);
};
#endif