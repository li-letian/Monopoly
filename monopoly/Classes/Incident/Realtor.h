#ifndef _REALTOR_H_
#define _REALTOR_H_

#include "Character/Character.h"
#include "Scene/MapScene.h"
#include "Land/Land.h"

//旅馆房价上涨
void SellPriceRise(Vector<Character*>& characters, MapScene* map_scene);

//旅馆房价下降
void SellPriceDown(Vector<Character*>& characters, MapScene* map_scene);

//旅馆租金上涨
void RentPriceUp(Vector<Character*>& characters, MapScene* map_scene);

//旅馆租金下降
void RentPriceDown(Vector<Character*>& characters, MapScene* map_scene);

//随机摧毁一栋房屋(不论所有者)
//函数返回值代表所有者是否有房，若有房返回true，否则为false
//当然在所有者一栋房都没有的时候也可以调用此函数，只不过不产生任何效果
bool DestroyOneRandomHouse(MapScene* map_scene);

//随机摧毁一条街上所有的房屋（不论所有者）
//函数返回值代表整个地图上是否有房，若有房返回true，否则为false
//当然在整个地图上都无房的时候也可以调用此函数，只不过不产生任何效果
bool DestroyOneRandomStreetHouse(MapScene* map_scene);

//强制拆除一栋房屋（指定所有者）
//函数返回值代表所有者是否有房，若有房返回true，否则为false
//当然在所有者一栋房都没有的时候也可以调用此函数，只不过不产生任何效果
bool DestroyOneCertainHouse(Character* character, MapScene* map_scene);

//强制征收一块地（指定所有者）
//函数执行后此土地无所有者
bool DestroyOneCertainHotel(Character* character, MapScene* map_scene);

#endif