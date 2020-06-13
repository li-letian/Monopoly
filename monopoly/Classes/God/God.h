#ifndef _GOD_H_
#define _GOD_H_
#include "cocos2d.h"

USING_NS_CC;

class Character;
class MapScene;

class God :public Sprite {
public:
	static God* createGod(int god_type);
	virtual bool onLand(Character* standing);
	bool setPos(int pos_index, MapScene* map_scene);
	int getPos()const;
	void removeGodFromMap();
	void addToCharacter(Character* standing);
	void popUpExplain(bool deal_with_land = true);

protected:
	God(const std::string& name);
	void initGodImage();

	int pos_index_;
	std::string name_;
};




#endif