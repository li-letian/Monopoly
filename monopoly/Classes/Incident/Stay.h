#ifndef _STAY_H_
#define _STAY_H_

#include"Incident/Incident.h"
#include"Common/CommonConstant.h"

class Stay : public Incident {
public:
	Stay(MapScene* map_scene, int stop_times = default_stop_times);
protected:
	int stop_times_;
};
#endif
