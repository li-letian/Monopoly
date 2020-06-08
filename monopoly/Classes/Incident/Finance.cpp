#include "Incident/Finance.h"
#include "Incident/PopUpLayer.h"
#include "Common/CommonConstant.h"
#include "Scene/StockScene.h"
void StockMarketUp()
{
	auto stock_scene = GetStockScene();
	stock_scene->setCondition(up_market);
	stock_scene->setDurationTime(market_duration_time);
}

void StockMarketDown()
{
	auto stock_scene = GetStockScene();
	stock_scene->setCondition(down_market);
	stock_scene->setDurationTime(market_duration_time);
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

