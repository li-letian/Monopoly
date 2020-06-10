#ifndef _REALTOR_H_
#define _REALTOR_H_

#include "cocos2d.h"
USING_NS_CC;
class Character;
class Hotel;
int GetRandomHotel();
//旅馆房价上涨
void SellPriceRise(int pos);

//旅馆房价下降
void SellPriceDown(int pos);

//旅馆租金上涨
void RentPriceUp(int pos);

//旅馆租金下降
void RentPriceDown(int pos);

//不是接口
void DestroyOneStreetHouse(int start_index);

//不是借口
void PromoteOneStreetHouse(int start_index);

//不是接口
void DestroyHouse(Hotel* hotel);

//不是接口
void SetSellPrice(float rise_rate, int pos);

//随机摧毁一栋房屋(不论所有者)
//函数返回值代表所有者是否有房，若有房返回true，否则为false
//当然在所有者一栋房都没有的时候也可以调用此函数，只不过不产生任何效果
bool DestroyOneRandomHouse();

//随机摧毁一条街上所有的房屋（不论所有者）
//函数返回值代表整个地图上是否有房，若有房返回true，否则为false
//当然在整个地图上都无房的时候也可以调用此函数，只不过不产生任何效果
bool DestroyOneRandomStreetHouse();

//强制拆除一栋房屋（指定所有者）
//函数返回值代表所有者是否有房，若有房返回true，否则为false
//当然在所有者一栋房都没有的时候也可以调用此函数，只不过不产生任何效果
bool DestroyOneCertainHouse(Character* character);

//强制征收一块地（指定所有者）
//函数执行后此土地无所有者
bool DestroyOneCertainHotel(Character* character);
#endif