#ifndef _COMMON_METHOD_H_
#define _COMMON_METHOD_H_

#include <cstdlib>
#include<string>

#define random(x) (rand()%x)

class MapScene;
class GameController;
class StockScene;
class ItemScene;
std::string ZH(const std::string& str);

void SendMsg(int msg);
MapScene* GetMapScene();
GameController* GetGameController();
StockScene* GetStockScene();
ItemScene* GetItemScene();
#endif // !_COMMON_METHOD_H_
