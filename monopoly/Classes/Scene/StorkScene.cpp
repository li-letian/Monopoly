#include "StorkScene.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"
#include <ctime>
#include <vector>
using namespace std;
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
	//this->storeNumber = storeNumber_;
	this->makeDealPrice = makeDealPrice_;
	int num[4] = { 0 };
	vector<int> vec(num, num + 4);
	this->storeNumber = vec;
	/*
	for (int i = 0; i < 4; i++) {
		this->storeNumber.pushBack(0);
	}
	*/

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
	auto stockSprite = Sprite::create("pic.png");
	stockSprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(stockSprite,24);
	StockInfInit(); //初始化股票信息
	
	initLabel();                       //考虑传进来stockVec
	return true;


}
void StockScene::initLabel() {
	

	Size VisibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小
	initFirstLabel();
	for (int i = 0; i < 8; i++) {
		Value valCode, valName, valPrice, valDeal,valPer,valLabel,valStore,valBlank, valpercent;
		
		valCode = Value(stockVec.at(i)->stockCode);
		valName = Value(stockVec.at(i)->stockName);
		valPrice = Value(stockVec.at(i)->nowPrice);
		valDeal = Value(stockVec.at(i)->makeDealPrice);
		valPer = Value(static_cast<int>((stockVec.at(i)->percent)*100));
		valStore = Value(stockVec.at(i)->storeNumber[0]);
		valpercent = "%";
		valBlank = Value("  ");
		valPer = valPer.asString().c_str() + valpercent.asString();
		valLabel = valCode.asString().c_str() +valBlank.asString()+valName.asString() + valBlank.asString() +
			valBlank.asString()+valPrice.asString().c_str() + valBlank.asString() + valBlank.asString() + valPer.asString().c_str() ;
			
		auto label = Label::createWithSystemFont(valLabel.asString().c_str(), "fonts/arial.ttf", 40);//创建一个标签
		if (valPer.asFloat() <= 0)
			label->setTextColor(Color4B::GREEN);
		else
			label->setTextColor(Color4B::RED);
		label->setAnchorPoint(Vec2(0, 0.5));
		label->setPosition(Vec2(5, VisibleSize.height - 197 - 64 * (1 + i)));
		this->addChild(label, 25);
		
		auto labelStore = Label::createWithSystemFont(valStore.asString().c_str(), "fonts/arial.ttf", 40);//创建一个标签
		if (valPer.asFloat() <= 0)
			labelStore->setTextColor(Color4B::GREEN);
		else
			labelStore->setTextColor(Color4B::RED);
		labelStore->setAnchorPoint(Vec2(0, 0.5));
		labelStore->setPosition(Vec2(500, VisibleSize.height - 197 - 64 * (1 + i)));
		this->addChild(labelStore, 25);
		
		auto labelBuy = Label::createWithSystemFont(ZH("买入"), "fonts/arial.ttf", 38);
		auto menuItem_buy= MenuItemLabel::create(labelBuy);
		menuItem_buy->setCallback([=](Ref* render) {
			
			});
		menuItem_buy->setAnchorPoint(Vec2(0, 0.5));
		menuItem_buy->setPosition(Vec2(590, VisibleSize.height - 197 - 64 * (1 + i)));
		this->addChild(menuItem_buy, 25);
		
			/*
				auto labelCode = Label::createWithSystemFont(valCode.asString().c_str(), "fonts/arial.ttf", 44);
				if (valPer.asFloat() <= 0)
					labelCode->setTextColor(Color4B::GREEN);
				else 
					labelCode->setTextColor(Color4B::RED);
				labelCode->setAnchorPoint(Vec2(0, 0.5));
				labelCode->setPosition(Vec2(5, VisibleSize.height - 197 - 64 * (1+i)));
				this->addChild(labelCode, 25);
				

			
				auto labelName = Label::createWithSystemFont(valName.asString().c_str(), "fonts/arial.ttf", 40);
				if (valPer.asFloat() <= 0)
					labelName->setTextColor(Color4B::GREEN);
				else
					labelName->setTextColor(Color4B::RED);
				labelName->setAnchorPoint(Vec2(0, 0.5));
				labelName->setPosition(Vec2(120, VisibleSize.height - 197 - 64 * (1+i)));
				this->addChild(labelName, 25);
				


			
				auto labelPrice = Label::createWithBMFont(valPrice.asString().c_str(), "fonts/arial.ttf", 46);
				if (valPer.asFloat() <= 0)
					labelPrice->setTextColor(Color4B::GREEN);
				else
					labelPrice->setTextColor(Color4B::RED);
				labelPrice->setAnchorPoint(Vec2(0, 0.5));
				labelPrice->setPosition(Vec2(310, VisibleSize.height - 197 - 64 * (1+i)));
				this->addChild(labelPrice, 25);
				

			
				auto labelPer = Label::createWithSystemFont(StringUtils::format("%.0f%%",valPer.asFloat()*100),"fonts/arial.ttf", 38);
				if (valPer.asFloat() <= 0)
					labelPer->setTextColor(Color4B::GREEN);
				else
					labelPer->setTextColor(Color4B::RED);
				labelPer->setAnchorPoint(Vec2(0, 0.5));
				labelPer->setPosition(Vec2(390, VisibleSize.height - 197 - 64 * (1+i)));
				this->addChild(labelPer, 25);
				
				auto labelStore = Label::createWithSystemFont(valStore.asString().c_str(), "fonts/arial.ttf", 46);
				if (valPer.asFloat() <= 0)
					labelStore->setTextColor(Color4B::GREEN);
				else
					labelStore->setTextColor(Color4B::RED);
				labelStore->setAnchorPoint(Vec2(0, 0.5));
				labelStore->setPosition(Vec2(500, VisibleSize.height - 197 - 64 * (1+i)));
				this->addChild(labelStore, 25);
			
			*/

		


	}




	
}
void StockScene::StockInfInit() {
	this->stockVec.pushBack(Stock::create(8010, ZH("天地银行"), 50, 0, static_cast < float>(0.0), 0));       //股票代码 股票名称 当前价格 成交价格 涨幅 持仓数 
	this->stockVec.pushBack(Stock::create(8011, ZH("宇宙房产"), 60, 0, static_cast < float>(0.01), 0));
	this->stockVec.pushBack(Stock::create(8012, ZH("玄学制药"), 30, 0, static_cast<float>(-0.09), 0));
	this->stockVec.pushBack(Stock::create(8015, ZH("缪斯学院"), 70, 0, static_cast < float>(0.04), 0));
	this->stockVec.pushBack(Stock::create(8016, ZH("保险公司"), 20, 0, static_cast < float>(0.01), 0));
	this->stockVec.pushBack(Stock::create(8017, ZH("石油公司"), 10, 0, static_cast < float>(0.08), 0));
	this->stockVec.pushBack(Stock::create(8018, ZH("科技公司"), 80, 0, static_cast < float>(0.03), 0));
	this->stockVec.pushBack(Stock::create(8019, ZH("航空公司"), 30, 0, static_cast < float>(0.07), 0));
}


void StockScene::initFirstLabel() {
	Size VisibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小
	auto labelCode = Label::createWithSystemFont(ZH("代码"), "fonts/arial.ttf", 40);
	
	labelCode->setTextColor(Color4B::BLACK);
	labelCode->setAnchorPoint(Vec2(0, 0.5));
	labelCode->setPosition(Vec2(5, VisibleSize.height - 197 ));
	this->addChild(labelCode, 25);



	auto labelName = Label::createWithSystemFont(ZH("股票名称"), "fonts/arial.ttf", 40);
	labelName->setTextColor(Color4B::BLACK);
	labelName->setAnchorPoint(Vec2(0, 0.5));
	labelName->setPosition(Vec2(120, VisibleSize.height - 197 ));
	this->addChild(labelName, 25);




	auto labelPrice = Label::createWithSystemFont(ZH("价格"), "fonts/arial.ttf", 40);
	labelPrice->setTextColor(Color4B::BLACK);
	labelPrice->setAnchorPoint(Vec2(0, 0.5));
	labelPrice->setPosition(Vec2(305, VisibleSize.height - 197 ));
	this->addChild(labelPrice, 25);



	auto labelPer = Label::createWithSystemFont(ZH("涨幅"), "fonts/arial.ttf", 40);
	labelPer->setTextColor(Color4B::BLACK);
	labelPer->setAnchorPoint(Vec2(0, 0.5));
	labelPer->setPosition(Vec2(390, VisibleSize.height - 197 ));
	this->addChild(labelPer, 25);

	auto labelStore = Label::createWithSystemFont(ZH("数量"), "fonts/arial.ttf", 40);
	labelStore->setTextColor(Color4B::BLACK);
	labelStore->setAnchorPoint(Vec2(0, 0.5));
	labelStore->setPosition(Vec2(495, VisibleSize.height - 197 ));
	this->addChild(labelStore, 25);
}

void StockScene::stockUpdate() {
	srand(time(0));
	for (int i = 0; i < 8; i++) {
		float per_ = rand() / (10*RAND_MAX+static_cast<float>(0.001));
		if (rand() % 2)per_ *= (-1.0);
		stockVec.at(i)->percent = per_;
		stockVec.at(i)->nowPrice *= (1.0+per_);

	}
}

void StockScene::remakeLabel(Character* player) {

	this->removeAllChildren();
	initFirstLabel();
	Size VisibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小
	
	for (int i = 0; i < 8; i++) {
		Value valCode, valName, valPrice, valDeal, valPer, valLabel, valStore, valBlank, valpercent;

		valCode = Value(stockVec.at(i)->stockCode);
		valName = Value(stockVec.at(i)->stockName);
		valPrice = Value(stockVec.at(i)->nowPrice);
		valDeal = Value(stockVec.at(i)->makeDealPrice);
		valPer = Value(static_cast<int>((stockVec.at(i)->percent) * 100));
		valStore = Value(stockVec.at(i)->storeNumber[(*player).getTag()]);
		valpercent = "%";
		valBlank = Value("  ");
		valPer = valPer.asString().c_str() + valpercent.asString();
		valLabel = valCode.asString().c_str() + valBlank.asString() + valName.asString() + valBlank.asString() +
			valBlank.asString() + valPrice.asString().c_str() + valBlank.asString() + valBlank.asString() + valPer.asString().c_str();

		auto label = Label::createWithSystemFont(valLabel.asString().c_str(), "fonts/arial.ttf", 40);//创建一个标签
		if (valPer.asFloat() <= 0)
			label->setTextColor(Color4B::GREEN);
		else
			label->setTextColor(Color4B::RED);
		label->setAnchorPoint(Vec2(0, 0.5));
		label->setPosition(Vec2(5, VisibleSize.height - 197 - 64 * (1 + i)));
		this->addChild(label, 25);

		auto labelStore = Label::createWithSystemFont(valStore.asString().c_str(), "fonts/arial.ttf", 40);//创建一个标签
		if (valPer.asFloat() <= 0)
			labelStore->setTextColor(Color4B::GREEN);
		else
			labelStore->setTextColor(Color4B::RED);
		labelStore->setAnchorPoint(Vec2(0, 0.5));
		labelStore->setPosition(Vec2(500, VisibleSize.height - 197 - 64 * (1 + i)));
		this->addChild(labelStore, 25);

		auto labelBuy = Label::createWithSystemFont(ZH("买入"), "fonts/arial.ttf", 38);
		auto menuItem_buy = MenuItemLabel::create(labelBuy);
		menuItem_buy->setCallback([=](Ref* render) {
			int money_ = player->getMoney;
			if (money_ >= valPrice.asInt() * 100) {
				player->setMoney(money_ - valPrice.asInt() * 100);
				stockVec.at(i)->storeNumber[player->getTag()] += 100;
				remakeLabel(player);

			}
			});
		menuItem_buy->setAnchorPoint(Vec2(0, 0.5));
		menuItem_buy->setPosition(Vec2(590, VisibleSize.height - 197 - 64 * (1 + i)));
		this->addChild(menuItem_buy, 25);

	}
}