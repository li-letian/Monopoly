#ifndef _FINANCE_H_
#define _FINANCE_H_

#include "Scene/StorkScene.h"

void StockMarketUp(StockScene* stock_scene);	//让股价持续上涨几回合
void StockMarketDown(StockScene* stock_scene);	//让股价持续下跌几回合
void PopUpMarketCalm(MapScene* map_scene);		//发送股市将要缓和的消息
void PopUpMarketRecover(MapScene* map_scene);	//发送股市将要复苏的消息

#endif