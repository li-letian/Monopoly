#ifndef __STORK_SCENE_H__
#define __STORK_SCENE_H__
#endif
#include "cocos2d.h"
class Stock :public cocos2d::Sprite {
private:
	int stockCode_;            //股票代码
	std::string stockName_;    //股票名称
	int nowPrice_;             //当前价格
	int makeDealPrice_;        //成交价格
	float percent_;            //涨幅
	int storeNumber_;          //持有数量

public:
	Stock(int stockCode_, std::string stockName_, int nowPrice_, int makeDealPrice_, float percent_, int storeNumber_);
	Stock* creat(int stockCode_, std::string stockName_, int nowPrice_, int makeDealPrice_, float percent_, int storeNumber_);
	
	 
};
class StockCellCard :public cocos2d::Sprite {
public:
	static StockCellCard* createCardSprite(int numbers, int width, int height, float spriteX, float spriteY);
	virtual bool init();
	CREATE_FUNC(StockCellCard);
	int getStockNumber();
	void setStockNumber(int num);
private:
	Label* stockLabel;
	LayerColor* layerColor;
};




//TableView:
const int stockCellWidth = 100;
const int stockCellHeight = 30;
const int buy_button = 801;
const int sell_button = 802;
const int back_button = 803;
const float spaceRatio = 0.08;
const float leftRatioX = 0.1;

class LineChart :public LayerColor, TableViewDataSource, TableViewDelegate {

};