#ifndef  STAFF_H_
#define  STAFF_H_

#include "cocos2d.h"
class Character;
USING_NS_CC;

//给指定角色配上加速鞋
//若角色已有加速鞋，返回false
bool SetSpeedShoes(Character* character);

//给指定角色配上飞鞋
//若角色已有飞鞋，返回false
bool SetFlyingShoes(Character* character);

//给指定角色加上乌龟卡的效果
//此举将摧毁角色的原有特殊鞋子
//若角色已在乌龟卡状态，返回false
bool SetTurtle(Character* character);

//摧毁特殊鞋子
//若角色无任何特殊鞋子，返回false
bool DestroySpecialShoes(Character* character);

//对指定角色使用遥控骰子
//若角色本回合已使用遥控骰子，返回false
bool SetControlDice(Character* character, int control_point);

//指定地点发射导弹
void LaunchMissile(Character* user, int target_point);

//对指定地点使用机器工人
//若不满足使用条件则返回false
bool UseRobotWorker(Character* user, int target_point);

//对指定地点使用恶魔卡
//若不满足使用条件则返回false
bool UseDevilCard(int target_point);

bool UseAngelCard(int target_poin);

//传送神到指定地点
bool TransmitGod();

//传送角色到指定地点,若角色状态不正常，返回false
bool TransmitCharacter(Character* user, Character* target, int target_point);

//摧毁一个指定房屋
//若指定位置无房屋则返回false
bool UseHouseDestroy(int target_point);

//交换两地的房屋
//若两地不可交换则返回false
bool UseHouseExchange(int house1_pos, int house2_pos);

//使用购地证明,强制购买一块当前所处的他人的土地
//若此地不可购买或钱不够买则返回false
bool UseHouseBuy(Character* user);

//使用改建证明
//若此地不可改建则返回false
bool UseHouseChange(int target_point);

//使用涨价卡
bool UseRisePriceCard(int target_point);

//使用红卡
void UseRedCard(Character* user);

//使用黑卡
void UseBlackCard(Character* user);

//使用均富卡
//若指定两人物不合理则返回false
bool UseAverageCard(Character* user, Character* target);

//使用停留卡
//若指定人物状态不正常则返回false
bool UseStayCard(Character* target);

//使用转向卡
//若指定人物状态不正常则返回false
bool UseTurnAroundCard(Character* user);

//使用强制度假卡，让所有对手都去度假
void UseHolidayCard(Character* user);
#endif // ! STAFF_H_