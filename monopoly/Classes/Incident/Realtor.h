#ifndef _REALTOR_H_
#define _REALTOR_H_

#include "cocos2d.h"
USING_NS_CC;
class Character;
class Hotel;
int GetRandomHotel();
//�ùݷ�������
void SellPriceRise(int pos);

//�ùݷ����½�
void SellPriceDown(int pos);

//�ù��������
void RentPriceUp(int pos);

//�ù�����½�
void RentPriceDown(int pos);

//���ǽӿ�
void DestroyOneStreetHouse(int start_index);

//���ǽ��
void PromoteOneStreetHouse(int start_index);

//���ǽӿ�
void DestroyHouse(Hotel* hotel);

//���ǽӿ�
void SetSellPrice(float rise_rate, int pos);

//����ݻ�һ������(����������)
//��������ֵ�����������Ƿ��з������з�����true������Ϊfalse
//��Ȼ��������һ������û�е�ʱ��Ҳ���Ե��ô˺�����ֻ�����������κ�Ч��
bool DestroyOneRandomHouse();

//����ݻ�һ���������еķ��ݣ����������ߣ�
//��������ֵ����������ͼ���Ƿ��з������з�����true������Ϊfalse
//��Ȼ��������ͼ�϶��޷���ʱ��Ҳ���Ե��ô˺�����ֻ�����������κ�Ч��
bool DestroyOneRandomStreetHouse();

//ǿ�Ʋ��һ�����ݣ�ָ�������ߣ�
//��������ֵ�����������Ƿ��з������з�����true������Ϊfalse
//��Ȼ��������һ������û�е�ʱ��Ҳ���Ե��ô˺�����ֻ�����������κ�Ч��
bool DestroyOneCertainHouse(Character* character);

//ǿ������һ��أ�ָ�������ߣ�
//����ִ�к��������������
bool DestroyOneCertainHotel(Character* character);
#endif