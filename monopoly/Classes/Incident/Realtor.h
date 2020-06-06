#ifndef _REALTOR_H_
#define _REALTOR_H_

class Character;

//�ùݷ�������
void SellPriceRise();

//�ùݷ����½�
void SellPriceDown();

//�ù��������
void RentPriceUp();

//�ù�����½�
void RentPriceDown();

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