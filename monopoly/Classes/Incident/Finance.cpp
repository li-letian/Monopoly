#include "Incident/Finance.h"
#include "Common/CommonConstant.h"
#include "Scene/MapScene.h"
#include "Incident/PopUpLayer.h"

void StockMarketUp(StockScene* stock_scene)
{
	stock_scene->setCondition(up_market);
	stock_scene->setDurationTime(market_duration_time);
}

void StockMarketDown(StockScene* stock_scene)
{
	stock_scene->setCondition(down_market);
	stock_scene->setDurationTime(market_duration_time);
}

void PopUpMarketCalm(MapScene* map_scene)
{
	auto pop = PopUpLayer::create();
	pop->setTitle("股市新闻");
	pop->setContent("股市似乎有趋于缓和的迹象");
	pop->setCallBack([=](Ref* sender) {
		
		});
	pop->setPosition(0, 0);
	map_scene->addChild(pop, 50);
}

void PopUpMarketRecover(MapScene* map_scene)
{
	auto pop = PopUpLayer::create();
	pop->setTitle("股市新闻");
	pop->setContent("股市似乎有复苏的迹象");
	pop->setCallBack([=](Ref* sender) {

		});
	pop->setPosition(0, 0);
	map_scene->addChild(pop, 50);
}

