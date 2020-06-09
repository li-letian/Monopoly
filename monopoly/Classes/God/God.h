#ifndef _GOD_H_
#define _GOD_H_
#include "cocos2d.h"

USING_NS_CC;

class MapScene;
class Character;

class God : public Sprite{
public:
	virtual bool onLand(Character* standing) = 0;
	bool setPos(int pos_index);
	int getPos()const;

protected:
	God(const std::string& name);
	void initGodImage();
	bool setPossesed(Character* standing, int god_type);
	int pos_index_;
	std::string name_;

private:
	void popUpExplain();
};




#endif