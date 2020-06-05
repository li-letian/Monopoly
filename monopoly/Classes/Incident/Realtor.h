#ifndef _REALTOR_H_
#define _REALTOR_H_

#include "Character/Character.h"
#include "Scene/MapScene.h"
#include "Land/Land.h"

//�ùݷ�������
void SellPriceRise(Vector<Character*>& characters, MapScene* map_scene);

//�ùݷ����½�
void SellPriceDown(Vector<Character*>& characters, MapScene* map_scene);

//�ù��������
void RentPriceUp(Vector<Character*>& characters, MapScene* map_scene);

//�ù�����½�
void RentPriceDown(Vector<Character*>& characters, MapScene* map_scene);

//����ݻ�һ������(����������)
//��������ֵ�����������Ƿ��з������з�����true������Ϊfalse
//��Ȼ��������һ������û�е�ʱ��Ҳ���Ե��ô˺�����ֻ�����������κ�Ч��
bool DestroyOneRandomHouse(MapScene* map_scene);

//����ݻ�һ���������еķ��ݣ����������ߣ�
//��������ֵ����������ͼ���Ƿ��з������з�����true������Ϊfalse
//��Ȼ��������ͼ�϶��޷���ʱ��Ҳ���Ե��ô˺�����ֻ�����������κ�Ч��
bool DestroyOneRandomStreetHouse(MapScene* map_scene);

//ǿ�Ʋ��һ�����ݣ�ָ�������ߣ�
//��������ֵ�����������Ƿ��з������з�����true������Ϊfalse
//��Ȼ��������һ������û�е�ʱ��Ҳ���Ե��ô˺�����ֻ�����������κ�Ч��
bool DestroyOneCertainHouse(Character* character, MapScene* map_scene);

//ǿ������һ��أ�ָ�������ߣ�
//����ִ�к��������������
bool DestroyOneCertainHotel(Character* character, MapScene* map_scene);

#endif