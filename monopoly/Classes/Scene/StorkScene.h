#ifndef _STORK_SCENE_H_
#define _STORK_SCENE_H_
#include "ZH.h"
#include "cocos2d.h"
using namespace cocos2d;

class Stock :public cocos2d::Sprite {
public:
	int stockCode_;            //��Ʊ����
	std::string stockName_;    //��Ʊ����
	int nowPrice_;             //��ǰ�۸�
	int makeDealPrice_;        //�ɽ��۸�
	float percent_;            //�Ƿ�
	int storeNumber_;          //��������

public:
	Stock(int stockCode_, std::string stockName_, int nowPrice_, int makeDealPrice_, float percent_, int storeNumber_);
	static Stock* create(int stockCode_, std::string stockName_, int nowPrice_, int makeDealPrice_, float percent_, int storeNumber_);
	
	 
};


class StockScene :public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(StockScene);
	void initLabel(Vector<Stock*> vec);
};
#endif