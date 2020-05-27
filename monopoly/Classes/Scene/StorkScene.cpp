#include "StorkScene.h"



Stock* Stock::creat(int stockCode_, std::string stockName, int nowPrice, int makeDealPrice, float percent, int storeNumber) {
	Stock* stock = new Stock(stockCode_,stockName,nowPrice,makeDealPrice,percent,storeNumber);
	stock->init();
	stock->autorelease();
	return stock;
}
Stock::Stock(int stockCode_, std::string stockName_, int nowPrice_, int makeDealPrice_, float percent_, int storeNumber_) {
	this->stockCode_ = stockCode_;
	this->stockName_ = stockName_;
	this->nowPrice_ = nowPrice_;
	this->percent_ = percent_;
	this->storeNumber_ = storeNumber_;
	this->makeDealPrice_ = makeDealPrice_;
	

}