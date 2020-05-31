#ifndef _LAND_H_
#define _LAND_H_

#include "cocos2d.h"

USING_NS_CC;

class MapScene;
class Land : public Sprite {
public:
	virtual bool onLand()
	{
		return true;
	}

	static void setMap(MapScene* map_scene)
	{
		map_scene_ = map_scene;
	}

protected:
	static MapScene* map_scene_;
};

#endif // !_LAND_H_
