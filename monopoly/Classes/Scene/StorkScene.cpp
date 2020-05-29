#include "StorkScene.h"
#include "ZH.h"
#include "Character/Character.h"

Stock* Stock::create(int stockCode_, std::string stockName, int nowPrice, int makeDealPrice, float percent, int storeNumber) {
	Stock* stock = new Stock(stockCode_,stockName,nowPrice,makeDealPrice,percent,storeNumber);
	//stock->init();
	//stock->autorelease();
	//return stock;
}
Stock::Stock(int stockCode_, std::string stockName_, int nowPrice_, int makeDealPrice_, float percent_, int storeNumber_) {
	this->stockCode_ = stockCode_;
	this->stockName_ = stockName_;
	this->nowPrice_ = nowPrice_;
	this->percent_ = percent_;
	this->storeNumber_ = storeNumber_;
	this->makeDealPrice_ = makeDealPrice_;
	

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
	initLabel(Character::getStockVec());                       //考虑传进来vec
	return true;


}
void StockScene::initLabel(Vector<Stock*> vec) {
	Size VisibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小
	for (int i = 0; i < 4; i++) {
		Value valCode, valName, valPrice, valDeal,valPer,valLabel;
		valCode = Value(vec.at(i)->stockCode_);
		valName = Value(vec.at(i)->stockName_);
		valPrice = Value(vec.at(i)->nowPrice_);
		valDeal = Value(vec.at(i)->makeDealPrice_);
		valPer = Value(vec.at(i)->percent_);
		Value valBlank(" ");
		
		valLabel = valCode.asString().c_str + valBlank.asString()+valName.asString() + valBlank.asString() +
			valPrice.asString().c_str() + valBlank.asString() + valDeal.asString().c_str() + valBlank.asString() +
			valPer.asString().c_str();

		auto label = Label::createWithSystemFont(valLabel.asString().c_str(), "fonts/arial.ttf", 30);//创建一个标签
		label->setTextColor(Color4B::GREEN);
		label->setAnchorPoint(Vec2(0, 0));
		label->setPosition(Vec2(0, VisibleSize.height - 36*(1+i)));//设置位置
		this->addChild(label);


	}





}
