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
	pop->setTitle("股市新闻");
	pop->setContent("股市似乎有趋于缓和的迹象");
	pop->setCallBack([=](Ref* sender) {
		
		});
	pop->setOnScene();
}

void PopUpMarketRecover()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("股市新闻");
	pop->setContent("股市似乎有复苏的迹象");
	pop->setCallBack([=](Ref* sender) {

		});
	pop->setOnScene();
}

