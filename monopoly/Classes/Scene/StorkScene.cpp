#include "StorkScene.h"
#include "Character/Character.h"
#include "Common/CommonMethod.h"
Stock* Stock::create(int stockCode_, std::string stockName, int nowPrice, int makeDealPrice, float percent, int storeNumber) {
	Stock* stock = new Stock(stockCode_,stockName,nowPrice,makeDealPrice,percent,storeNumber);
	stock->init();
	stock->autorelease();
	return stock;
}
Stock::Stock(int stockCode_, std::string stockName_, int nowPrice_, int makeDealPrice_, float percent_, int storeNumber_) {
	this->stockCode = stockCode_;
	this->stockName = stockName_;
	this->nowPrice = nowPrice_;
	this->percent = percent_;
	this->storeNumber = storeNumber_;
	this->makeDealPrice = makeDealPrice_;
	

}
Scene* StockScene::createScene() {
	auto scene = Scene::create();
	auto layer = StockScene::create();
	scene->addChild(layer);
	return scene;

}
bool StockScene::init() {
	if (!Layer::init()) {
		return false;
	}
	StockInfInit();                            //初始化股票信息
	initLabel(stockVec);                       //考虑传进来vec
	return true;


}
void StockScene::initLabel(Vector<Stock*> vec) {
	Size VisibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小
	for (int i = 0; i < 4; i++) {
		Value valCode, valName, valPrice, valDeal,valPer,valLabel;
		
		valCode = Value(vec.at(i)->stockCode);
		valName = Value(vec.at(i)->stockName);
		valPrice = Value(vec.at(i)->nowPrice);
		valDeal = Value(vec.at(i)->makeDealPrice);
		valPer = Value(vec.at(i)->percent);
		Value valBlank(" ");
		/*
		valCode = Value(80010);
		valName = Value("abc");
		valPrice = Value(123);
		valDeal = Value(1234);
		valPer = Value(0.7);
		Value valBlank("1");
		*/

		valLabel = valCode.asString().c_str() + valBlank.asString()+valName.asString() + valBlank.asString() +
			valPrice.asString().c_str() + valBlank.asString() + valDeal.asString().c_str() + valBlank.asString() +
			valPer.asString().c_str();
			
		auto label = Label::createWithSystemFont(valLabel.asString().c_str(), "fonts/arial.ttf", 46);//创建一个标签
		//auto label = Label::createWithSystemFont("1111", "fonts/arial.ttf", 30);
		if(valPer.asFloat()<0)
		label->setTextColor(Color4B::GREEN);
		else if(valPer.asFloat() == 0)
		label->setTextColor(Color4B::BLACK);
		else label->setTextColor(Color4B::RED);

		label->setAnchorPoint(Vec2(0, 0));
		label->setPosition(Vec2(0, VisibleSize.height -48-72*(1+i)));//设置位置
		this->addChild(label);


	}





}
void StockScene::StockInfInit() {
	this->stockVec.pushBack(Stock::create(80010, ZH("天地银行"), 50, 0, 0, 0));
	this->stockVec.pushBack(Stock::create(80011, ZH("宇宙房产"), 60, 0, 0, 0));
	this->stockVec.pushBack(Stock::create(80012, ZH("玄学制药"), 30, 0, 0, 0));
	this->stockVec.pushBack(Stock::create(80015, ZH("缪斯学院"), 70, 0, 0, 0));

}
