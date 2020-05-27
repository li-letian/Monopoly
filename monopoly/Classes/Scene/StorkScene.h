#ifndef __STORK_SCENE_H__
#define __STORK_SCENE_H__
#endif
#include "cocos2d.h"
class Stock :public cocos2d::Sprite {
private:
	int stockCode_;            //��Ʊ����
	std::string stockName_;    //��Ʊ����
	int nowPrice_;             //��ǰ�۸�
	int makeDealPrice_;        //�ɽ��۸�
	float percent_;            //�Ƿ�
	int storeNumber_;          //��������

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