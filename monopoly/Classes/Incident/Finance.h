#ifndef _FINANCE_H_
#define _FINANCE_H_

#include "Scene/StorkScene.h"

//�ùɼ۳������Ǽ��غ�
void StockMarketUp(StockScene* stock_scene);
//�ùɼ۳����µ����غ�
void StockMarketDown(StockScene* stock_scene);
//���͹��н�Ҫ���͵���Ϣ
void PopUpMarketCalm(MapScene* map_scene);	
//���͹��н�Ҫ���յ���Ϣ
void PopUpMarketRecover(MapScene* map_scene);

#endif