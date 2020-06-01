#ifndef _STORK_SCENE_H_
#define _STORK_SCENE_H_
#include "cocos2d.h"
#include <vector>
using namespace std;
using namespace cocos2d;

class Stock :public cocos2d::Sprite {
public:
	int stock_code_;            //��Ʊ����
	std::string stock_name_;    //��Ʊ����
	int now_price_;             //��ǰ�۸�
	int make_deal_price_;        //�ɽ��۸�
	float percent_;            //�Ƿ�
	vector<int> store_number_;          //��������

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
	void stockInfInit();    //��Ʊ��ʼ��
    Vector<Stock*>stock_vec_; //��Ʊvector
	void initFirstLabel();
	void stockUpdate();
	void remakeLabel(Character* player);
};
#endif