#ifndef _FINANCE_H_
#define _FINANCE_H_

#include "Scene/StorkScene.h"

void StockMarketUp(StockScene* stock_scene);	//�ùɼ۳������Ǽ��غ�
void StockMarketDown(StockScene* stock_scene);	//�ùɼ۳����µ����غ�
void PopUpMarketCalm(MapScene* map_scene);		//���͹��н�Ҫ���͵���Ϣ
void PopUpMarketRecover(MapScene* map_scene);	//���͹��н�Ҫ���յ���Ϣ

#endif