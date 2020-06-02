#ifndef _CHRIMINAL_H_
#define _CHRIMINAL_H_

#include "Incident/Stay.h"

class Criminal :public Stay {
public:
	Criminal(MapScene* map_scene, int stop_times);
	virtual bool eventTrigger(Character* character);
	void popUpDialog();
	static void popUpDialog(Character* character, MapScene* map_scene);
};

#endif