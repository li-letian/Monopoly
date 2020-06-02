#ifndef _ECONOMY_H_
#define _ECONOMY_H_

#include "Character/Character.h"
//������������˰���ز�˰
//��ý������˵�˰ͬʱ������
//�����ķ���ֵΪ���յ���Ŀ
int LevyIncomeTax(Character* character);
int LevyEstateTax(Character* character);

Character* GetMostEstate(const Vector<Character*>& characters); //��֪�ز��������˭
Character* GetLeastEstate(const Vector<Character*>& characters); //��֪�ز���������˭
void RewardMostEstate(Character*character);	//�����ز������
void HelpLeastEstate(Character* character);	//�����ز�������

#endif
