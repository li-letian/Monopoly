#ifndef _STORK_SCENE_H_
#define _STORK_SCENE_H_
#include "cocos2d.h"
#include <vector>
using namespace std;
using namespace cocos2d;

class Stock :public cocos2d::Sprite {
public:
	int stock_code_;            //股票代码
	std::string stock_name_;    //股票名称
	int now_price_;             //当前价格
	int make_deal_price_;        //成交价格
	float percent_;            //涨幅
	vector<int> store_number_;          //持有数量

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
	void stockInfInit();    //股票初始化
    Vector<Stock*>stock_vec_; //股票vector
	void initFirstLabel();
	void stockUpdate();
	void remakeLabel(Character* player);
};
#endif