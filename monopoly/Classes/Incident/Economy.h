#ifndef _ECONOMY_H_
#define _ECONOMY_H_

#include "Character/Character.h"
#include "Scene/StockScene.h"
//��ý������˵�˰ͬʱ������
//�����ķ���ֵΪ���յ���Ŀ

//������������˰
int LevyIncomeTax(Character* character);
//�������յز�˰
int LevyEstateTax(Character* character);
//�������չ�Ʊ˰
int LevyStockTax(Character* character, StockScene* stock_scene);

//��֪�ز��������˭
Character* GetMostEstate(const Vector<Character*>& characters); 
//��֪�ز���������˭
Character* GetLeastEstate(const Vector<Character*>& characters);
//��֪��Ʊ�������˭
Character* GetMostStock(const Vector<Character*>& characters,StockScene*stock_scene);

//�����ز������
void RewardMostEstate(Character*character);
//�����ز�������
void HelpLeastEstate(Character* character);
//������Ʊӵ�������
void RewardMostStock(Character* character);

#endif
