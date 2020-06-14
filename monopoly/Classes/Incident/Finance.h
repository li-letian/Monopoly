#ifndef _FINANCE_H_
#define _FINANCE_H_

#include "cocos2d.h"
USING_NS_CC;
//让股价持续上涨几回合
void StockMarketUp();
//让股价持续下跌几回合
void StockMarketDown();
//发送股市将要缓和的消息
void PopUpMarketCalm();	
//发送股市将要复苏的消息
void PopUpMarketRecover();

#endif