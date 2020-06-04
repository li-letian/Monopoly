#ifndef _REALTOR_H_
#define _REALTOR_H_

#include "Character/Character.h"
#include "Scene/MapScene.h"

void SetSellPrice(Vector<Character*>characters, MapScene* map_scene, float rise_rate);//不为接口
void SetRentPrice(Vector<Character*>characters, MapScene* map_scene, float rise_rate);//不为接口

void SellPriceUp(Vector<Character*>characters, MapScene* map_scene);	//旅馆房价上涨
void SellPriceDown(Vector<Character*>characters, MapScene* map_scene);	//旅馆房价下降
void RentPriceUp(Vector<Character*>characters, MapScene* map_scene);	//旅馆租金上涨
void RentPriceDown(Vector<Character*>characters, MapScene* map_scene);	//旅馆租金下降

#endif