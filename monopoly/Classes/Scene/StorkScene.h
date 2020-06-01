#ifndef _STORK_SCENE_H_
#define _STORK_SCENE_H_
#include "cocos2d.h"
#include <vector>
using namespace std;
using namespace cocos2d;

class Stock :public cocos2d::Sprite {
public:
	int stockCode;            //股票代码
	std::string stockName;    //股票名称
	int nowPrice;             //当前价格
	int makeDealPrice;        //成交价格
	float percent;            //涨幅
	vector<int> storeNumber;          //持有数量

public:
	Stock(int stockCode_, std::string stockName_, int nowPrice_, int makeDealPrice_, float percent_, int storeNumber_);
	static Stock* create(int stockCode_, std::string stockName_, int nowPrice_, int makeDealPrice_, float percent_, int storeNumber_);

	 
};


class StockScene :public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(StockScene);
	void initLabel();
	void StockInfInit();    //股票初始化
    Vector<Stock*>stockVec; //股票vector
	void initFirstLabel();
	void stockUpdate();
	void remakeLabel(Character* player );
};
#endif