#ifndef _STORK_SCENE_H_
#define _STORK_SCENE_H_
#include "cocos2d.h"
#include <vector>
using namespace std;
using namespace cocos2d;

class Stock :public cocos2d::Sprite {
public:
	int stockCode;            //��Ʊ����
	std::string stockName;    //��Ʊ����
	int nowPrice;             //��ǰ�۸�
	int makeDealPrice;        //�ɽ��۸�
	float percent;            //�Ƿ�
	vector<int> storeNumber;          //��������

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
	void StockInfInit();    //��Ʊ��ʼ��
    Vector<Stock*>stockVec; //��Ʊvector
	void initFirstLabel();
	void stockUpdate();
	void remakeLabel(Character* player );
};
#endif