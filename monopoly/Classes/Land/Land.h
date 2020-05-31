#ifndef _LAND_H_
#define _LAND_H_

#include "cocos2d.h"
#include "Character/Character.h"

USING_NS_CC;

class MapScene;
class Land : public Sprite {
public:
	virtual bool onLand(Character* standing)
	{
		return true;
	}
	virtual bool promote()
	{
		return true;
	}
	virtual bool demote()
	{
		return true;
	}

	void setMapScene(MapScene* map_scene)
	{
		map_scene_ = map_scene;
	}
	MapScene* getMapScene()const
	{
		return map_scene_;
	}

protected:
	MapScene* map_scene_=nullptr;
	int index_ = 0;
};

#endif // !_LAND_H_
