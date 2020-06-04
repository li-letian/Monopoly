#ifndef _ECONOMY_H_
#define _ECONOMY_H_

#include "Character/Character.h"
#include "Scene/StorkScene.h"
//������������˰���ز�˰����Ʊ˰
//��ý������˵�˰ͬʱ������
//�����ķ���ֵΪ���յ���Ŀ
int LevyIncomeTax(Character* character);
int LevyEstateTax(Character* character);
int LevyStockTax(Character* character, StockScene* stock_scene);

Character* GetMostEstate(const Vector<Character*>& characters); //��֪�ز��������˭
Character* GetLeastEstate(const Vector<Character*>& characters);//��֪�ز���������˭
Character* GetMostStock(const Vector<Character*>& characters,StockScene*stock_scene);//��֪��Ʊ�������˭
void RewardMostEstate(Character*character);	//�����ز������
void HelpLeastEstate(Character* character);	//�����ز�������
void RewardMostStock(Character* character); //������Ʊӵ�������

#endif
