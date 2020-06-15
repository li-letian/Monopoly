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
	int stock_code_;            //��Ʊ����
	std::string stock_name_;    //��Ʊ����
	int now_price_;             //��ǰ�۸�
	int make_deal_price_;        //�ɽ��۸�
	float percent_;            //�Ƿ�
	vector<int> store_number_;          //��������

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
	void stockInfInit();    //��Ʊ��ʼ��
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
	Vector<Stock*>stock_vec_; //��Ʊvector
	MapScene* map_scene_ = nullptr;
	CC_SYNTHESIZE(int, condition_, Condition);
	CC_SYNTHESIZE(int, duration_time_, DurationTime);
};
#endif