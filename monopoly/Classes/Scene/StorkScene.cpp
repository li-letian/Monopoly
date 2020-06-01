#include "StorkScene.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"
#include <ctime>
#include <vector>
using namespace std;
Stock* Stock::create(int stock_code, std::string stock_name, int now_price, int make_deal_price, float percent, int store_number) {
	Stock* stock = new Stock(stock_code,stock_name,now_price,make_deal_price,percent,store_number);
	stock->init();
	stock->autorelease();
	return stock;
}
Stock::Stock(int stock_code, std::string stock_name, int now_price, int make_deal_price, float percent, int store_number) {
	this->stock_code_ = stock_code;
	this->stock_name_ = stock_name;
	this->now_price_ = now_price;
	this->percent_ = percent_;
	//this->store_number_ = store_number__;
	this->make_deal_price_ = make_deal_price;
	int num[4] = { 0 };
	vector<int> vec(num, num + 4);
	this->store_number_ = vec;
	/*
	for (int i = 0; i < 4; i++) {
		this->store_number_.pushBack(0);
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
	stockInfInit(); //��ʼ����Ʊ��Ϣ
	
	initLabel();                       //���Ǵ�����stock_vec_
	return true;


}
void StockScene::initLabel() {
	

	Size VisibleSize = Director::getInstance()->getVisibleSize();	//�����Ļ��С
	initFirstLabel();
	for (int i = 0; i < 8; i++) {
		Value valCode, valName, valPrice, valDeal,valPer,valLabel,valStore,valBlank, valpercent_;
		
		valCode = Value(stock_vec_.at(i)->stock_code_);
		valName = Value(stock_vec_.at(i)->stock_name_);
		valPrice = Value(stock_vec_.at(i)->now_price_);
		valDeal = Value(stock_vec_.at(i)->make_deal_price_);
		valPer = Value(static_cast<int>((stock_vec_.at(i)->percent_)*100));
		valStore = Value(stock_vec_.at(i)->store_number_[0]);
		valpercent_ = "%";
		valBlank = Value("  ");
		valPer = valPer.asString().c_str() + valpercent_.asString();
		valLabel = valCode.asString().c_str() +valBlank.asString()+valName.asString() + valBlank.asString() +
			valBlank.asString()+valPrice.asString().c_str() + valBlank.asString() + valBlank.asString() + valPer.asString().c_str() ;
			
		auto label = Label::createWithSystemFont(valLabel.asString().c_str(), "fonts/arial.ttf", 40);//����һ����ǩ
		if (valPer.asFloat() <= 0)
			label->setTextColor(Color4B::GREEN);
		else
			label->setTextColor(Color4B::RED);
		label->setAnchorPoint(Vec2(0, 0.5));
		label->setPosition(Vec2(5, VisibleSize.height - 197 - 64 * (1 + i)));
		this->addChild(label, 25);
		
		auto label_store = Label::createWithSystemFont(valStore.asString().c_str(), "fonts/arial.ttf", 40);//����һ����ǩ
		if (valPer.asFloat() <= 0)
			label_store->setTextColor(Color4B::GREEN);
		else
			label_store->setTextColor(Color4B::RED);
		label_store->setAnchorPoint(Vec2(0, 0.5));
		label_store->setPosition(Vec2(500, VisibleSize.height - 197 - 64 * (1 + i)));
		this->addChild(label_store, 25);
		
		auto labelBuy = Label::createWithSystemFont(ZH("����"), "fonts/arial.ttf", 38);
		auto menuItem_buy= MenuItemLabel::create(labelBuy);
		menuItem_buy->setCallback([=](Ref* render) {
			
			});
		menuItem_buy->setAnchorPoint(Vec2(0, 0.5));
		menuItem_buy->setPosition(Vec2(590, VisibleSize.height - 197 - 64 * (1 + i)));
		this->addChild(menuItem_buy, 25);
		
			/*
				auto label_code = Label::createWithSystemFont(valCode.asString().c_str(), "fonts/arial.ttf", 44);
				if (valPer.asFloat() <= 0)
					label_code->setTextColor(Color4B::GREEN);
				else 
					label_code->setTextColor(Color4B::RED);
				label_code->setAnchorPoint(Vec2(0, 0.5));
				label_code->setPosition(Vec2(5, VisibleSize.height - 197 - 64 * (1+i)));
				this->addChild(label_code, 25);
				

			
				auto label_name = Label::createWithSystemFont(valName.asString().c_str(), "fonts/arial.ttf", 40);
				if (valPer.asFloat() <= 0)
					label_name->setTextColor(Color4B::GREEN);
				else
					label_name->setTextColor(Color4B::RED);
				label_name->setAnchorPoint(Vec2(0, 0.5));
				label_name->setPosition(Vec2(120, VisibleSize.height - 197 - 64 * (1+i)));
				this->addChild(label_name, 25);
				


			
				auto label_price = Label::createWithBMFont(valPrice.asString().c_str(), "fonts/arial.ttf", 46);
				if (valPer.asFloat() <= 0)
					label_price->setTextColor(Color4B::GREEN);
				else
					label_price->setTextColor(Color4B::RED);
				label_price->setAnchorPoint(Vec2(0, 0.5));
				label_price->setPosition(Vec2(310, VisibleSize.height - 197 - 64 * (1+i)));
				this->addChild(label_price, 25);
				

			
				auto label_per = Label::createWithSystemFont(StringUtils::format("%.0f%%",valPer.asFloat()*100),"fonts/arial.ttf", 38);
				if (valPer.asFloat() <= 0)
					label_per->setTextColor(Color4B::GREEN);
				else
					label_per->setTextColor(Color4B::RED);
				label_per->setAnchorPoint(Vec2(0, 0.5));
				label_per->setPosition(Vec2(390, VisibleSize.height - 197 - 64 * (1+i)));
				this->addChild(label_per, 25);
				
				auto label_store = Label::createWithSystemFont(valStore.asString().c_str(), "fonts/arial.ttf", 46);
				if (valPer.asFloat() <= 0)
					label_store->setTextColor(Color4B::GREEN);
				else
					label_store->setTextColor(Color4B::RED);
				label_store->setAnchorPoint(Vec2(0, 0.5));
				label_store->setPosition(Vec2(500, VisibleSize.height - 197 - 64 * (1+i)));
				this->addChild(label_store, 25);
			
			*/

		


	}




	
}
void StockScene::stockInfInit() {
	this->stock_vec_.pushBack(Stock::create(8010, ZH("�������"), 50, 0, static_cast < float>(0.0), 0));       //��Ʊ���� ��Ʊ���� ��ǰ�۸� �ɽ��۸� �Ƿ� �ֲ��� 
	this->stock_vec_.pushBack(Stock::create(8011, ZH("���淿��"), 60, 0, static_cast < float>(0.01), 0));
	this->stock_vec_.pushBack(Stock::create(8012, ZH("��ѧ��ҩ"), 30, 0, static_cast<float>(-0.09), 0));
	this->stock_vec_.pushBack(Stock::create(8015, ZH("��˹ѧԺ"), 70, 0, static_cast < float>(0.04), 0));
	this->stock_vec_.pushBack(Stock::create(8016, ZH("���չ�˾"), 20, 0, static_cast < float>(0.01), 0));
	this->stock_vec_.pushBack(Stock::create(8017, ZH("ʯ�͹�˾"), 10, 0, static_cast < float>(0.08), 0));
	this->stock_vec_.pushBack(Stock::create(8018, ZH("�Ƽ���˾"), 80, 0, static_cast < float>(0.03), 0));
	this->stock_vec_.pushBack(Stock::create(8019, ZH("���չ�˾"), 30, 0, static_cast < float>(0.07), 0));
}


void StockScene::initFirstLabel() {
	Size VisibleSize = Director::getInstance()->getVisibleSize();	//�����Ļ��С
	auto label_code = Label::createWithSystemFont(ZH("����"), "fonts/arial.ttf", 40);
	
	label_code->setTextColor(Color4B::BLACK);
	label_code->setAnchorPoint(Vec2(0, 0.5));
	label_code->setPosition(Vec2(5, VisibleSize.height - 197 ));
	this->addChild(label_code, 25);



	auto label_name = Label::createWithSystemFont(ZH("��Ʊ����"), "fonts/arial.ttf", 40);
	label_name->setTextColor(Color4B::BLACK);
	label_name->setAnchorPoint(Vec2(0, 0.5));
	label_name->setPosition(Vec2(120, VisibleSize.height - 197 ));
	this->addChild(label_name, 25);




	auto label_price = Label::createWithSystemFont(ZH("�۸�"), "fonts/arial.ttf", 40);
	label_price->setTextColor(Color4B::BLACK);
	label_price->setAnchorPoint(Vec2(0, 0.5));
	label_price->setPosition(Vec2(305, VisibleSize.height - 197 ));
	this->addChild(label_price, 25);



	auto label_per = Label::createWithSystemFont(ZH("�Ƿ�"), "fonts/arial.ttf", 40);
	label_per->setTextColor(Color4B::BLACK);
	label_per->setAnchorPoint(Vec2(0, 0.5));
	label_per->setPosition(Vec2(390, VisibleSize.height - 197 ));
	this->addChild(label_per, 25);

	auto label_store = Label::createWithSystemFont(ZH("����"), "fonts/arial.ttf", 40);
	label_store->setTextColor(Color4B::BLACK);
	label_store->setAnchorPoint(Vec2(0, 0.5));
	label_store->setPosition(Vec2(495, VisibleSize.height - 197 ));
	this->addChild(label_store, 25);
}

void StockScene::stockUpdate() {
	srand(time(0));
	for (int i = 0; i < 8; i++) {
		float per_ = rand() / (10*RAND_MAX+static_cast<float>(0.001));
		if (rand() % 2)per_ *= (-1.0);
		stock_vec_.at(i)->percent_ = per_;
		stock_vec_.at(i)->now_price_ *= (1.0+per_);

	}
}

void StockScene::remakeLabel(Character* player) {

	this->removeAllChildren();
	initFirstLabel();
	Size VisibleSize = Director::getInstance()->getVisibleSize();	//�����Ļ��С
	
	for (int i = 0; i < 8; i++) {
		Value val_code, val_name, val_price, val_deal, val_per, valLabel_, val_store, val_blank, val_percent;

		val_code = Value(stock_vec_.at(i)->stock_code_);
		val_name = Value(stock_vec_.at(i)->stock_name_);
		val_price = Value(stock_vec_.at(i)->now_price_);
		val_deal = Value(stock_vec_.at(i)->make_deal_price_);
		val_per = Value(static_cast<int>((stock_vec_.at(i)->percent_) * 100));
		val_store = Value(stock_vec_.at(i)->store_number_[(*player).getTag()]);
		val_percent = "%";
		val_blank = Value("  ");
		val_per = val_per.asString().c_str() + val_percent.asString();
		valLabel_ = val_code.asString().c_str() + val_blank.asString() + val_name.asString() + val_blank.asString() +
			val_blank.asString() + val_price.asString().c_str() + val_blank.asString() + val_blank.asString() + val_per.asString().c_str();

		auto label_ = Label::createWithSystemFont(valLabel_.asString().c_str(), "fonts/arial.ttf", 40);//����һ����ǩ
		if (val_per.asFloat() <= 0)
			label_->setTextColor(Color4B::GREEN);
		else
			label_->setTextColor(Color4B::RED);
		label_->setAnchorPoint(Vec2(0, 0.5));
		label_->setPosition(Vec2(5, VisibleSize.height - 197 - 64 * (1 + i)));
		this->addChild(label_, 25);

		auto label_store = Label::createWithSystemFont(val_store.asString().c_str(), "fonts/arial.ttf", 40);//����һ����ǩ
		if (val_per.asFloat() <= 0)
			label_store->setTextColor(Color4B::GREEN);
		else
			label_store->setTextColor(Color4B::RED);
		label_store->setAnchorPoint(Vec2(0, 0.5));
		label_store->setPosition(Vec2(500, VisibleSize.height - 197 - 64 * (1 + i)));
		this->addChild(label_store, 25);

		auto labelBuy = Label::createWithSystemFont(ZH("����"), "fonts/arial.ttf", 38);
		auto menuItem_buy = MenuItemLabel::create(labelBuy);
		menuItem_buy->setCallback([=](Ref* render) {

			
			}
			);
		menuItem_buy->setAnchorPoint(Vec2(0, 0.5));
		menuItem_buy->setPosition(Vec2(590, VisibleSize.height - 197 - 64 * (1 + i)));
		this->addChild(menuItem_buy, 25);

	}
}