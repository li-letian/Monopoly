#ifndef _COMMON_METHOD_H_
#define _COMMON_METHOD_H_

#include <cstdlib>
#include<string>
#include "cocos2d.h"
USING_NS_CC;
#define random(x) (rand()%x)

class MapScene;
class GameController;
class StockScene;
std::string ZH(const std::string& str);

void SendMsg(int msg);
MapScene* GetMapScene();
GameController* GetGameController();
StockScene* GetStockScene();
#endif // !_COMMON_METHOD_H_
