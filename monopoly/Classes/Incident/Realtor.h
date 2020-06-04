#ifndef _REALTOR_H_
#define _REALTOR_H_

#include "Character/Character.h"
#include "Scene/MapScene.h"

void SetSellPrice(Vector<Character*>characters, MapScene* map_scene, float rise_rate);//��Ϊ�ӿ�
void SetRentPrice(Vector<Character*>characters, MapScene* map_scene, float rise_rate);//��Ϊ�ӿ�

void SellPriceUp(Vector<Character*>characters, MapScene* map_scene);	//�ùݷ�������
void SellPriceDown(Vector<Character*>characters, MapScene* map_scene);	//�ùݷ����½�
void RentPriceUp(Vector<Character*>characters, MapScene* map_scene);	//�ù��������
void RentPriceDown(Vector<Character*>characters, MapScene* map_scene);	//�ù�����½�

#endif