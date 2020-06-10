#ifndef _GOD_H_
#define _GOD_H_
#include "cocos2d.h"

USING_NS_CC;

class Character;
class MapScene;

class God :public Sprite {
public:
	virtual bool onLand(Character* standing) = 0;
	bool setPos(int pos_index, MapScene* map_scene);
	int getPos()const;

protected:
	God(const std::string& name);
	void initGodImage();
	bool removeGodFromMap(Character* standing);
	void addToCharacter(God*god,Character* standing);
	void popUpExplain(const std::string& name, int god_type);
	int pos_index_;
	std::string name_;
};




#endif