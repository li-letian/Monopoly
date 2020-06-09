#include "Incident/Finance.h"
#include "Incident/PopUpLayer.h"
#include "Common/CommonConstant.h"
#include "Scene/StockScene.h"

void SetStockMarket(int up_or_down)
{
	auto stock_scene = GetStockScene();
	stock_scene->setCondition(up_or_down);
	stock_scene->setDurationTime(market_duration_time);
	auto stocks = stock_scene->getStock();
	for (auto stock : stocks)
	{
		stock->setCondition(up_or_down);
		stock->setDurationTime(market_duration_time);
	}
}

void StockMarketUp()
{
	SetStockMarket(up_market);
}

void StockMarketDown()
{
	SetStockMarket(down_market);
}

void PopUpMarketCalm()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("��������");
	pop->setContent("�����ƺ������ڻ��͵ļ���");
	pop->setCallBack([=](Ref* sender) {
		
		});
	pop->setOnScene();
}

void PopUpMarketRecover()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("��������");
	pop->setContent("�����ƺ��и��յļ���");
	pop->setCallBack([=](Ref* sender) {

		});
	pop->setOnScene();
}

