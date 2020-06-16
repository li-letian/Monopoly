#ifndef _STOCK_SCENE_H_
#define _STOCK_SCENE_H_
#include "cocos2d.h"
#include <vector>
using namespace std;
using namespace cocos2d;
#include "Character/Character.h"

class MapScene;
class Stock :public cocos2d::Sprite {
public:
	int stock_code_;            //股票代码
	std::string stock_name_;    //股票名称
	int now_price_;             //当前价格
	int make_deal_price_;        //成交价格
	float percent_;            //涨幅
	vector<int> store_number_;          //持有数量

public:
	vector<int>& getStore() 
	{
		return store_number_;
	}
	Stock(int stock_code, std::string stock_name, int now_price, int make_deal_price, float percent, int store_number);
	static Stock* create(int stock_code, std::string stock_name, int now_price, int make_deal_price, float percent, int store_number);

	CC_SYNTHESIZE(int, condition_, Condition);
	CC_SYNTHESIZE(int, duration_time_, DurationTime);
};


class StockScene :public Layer {
public:
	static StockScene* StockScene::createScene(MapScene* map_scene);
	virtual bool init();
	CREATE_FUNC(StockScene);
	void initLabel();
	void stockInfInit();    //股票初始化
	Vector<Stock*>& getStock()
	{
		return stock_vec_;
	}
	void initFirstLabel();
	void stockUpdate();
	void remakeLabel(Character* player);
	void open(Ref* ref);
	void close(Ref* ref);

protected:
	bool is_open_ = false;
	Vector<Stock*>stock_vec_; //股票vector
	MapScene* map_scene_ = nullptr;
	CC_SYNTHESIZE(int, condition_, Condition);
	CC_SYNTHESIZE(int, duration_time_, DurationTime);
};
#endif