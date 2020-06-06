#ifndef _ECONOMY_H_
#define _ECONOMY_H_

class Character;
//��ý������˵�˰ͬʱ������
//�����ķ���ֵΪ���յ���Ŀ

//������������˰
int LevyIncomeTax(Character* character);
//�������յز�˰
int LevyEstateTax(Character* character);
//�������չ�Ʊ˰
int LevyStockTax(Character* character);

//��֪�ز��������˭
Character* GetMostEstate(); 
//��֪�ز���������˭
Character* GetLeastEstate();
//��֪��Ʊ�������˭
Character* GetMostStock();

//�����ز������
void RewardMostEstate(Character*character);
//�����ز�������
void HelpLeastEstate(Character* character);
//������Ʊӵ�������
void RewardMostStock(Character* character);

//��ͨԭ�򷣿�
void TraficFine(Character* character);
#endif
