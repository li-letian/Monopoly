#ifndef  STAFF_H_
#define  STAFF_H_

class Character;

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
#endif // ! STAFF_H_

//对指定角色使用遥控骰子
//若角色本回合已使用遥控骰子，返回false
bool SetControlDice(Character* character, int control_point);

//指定地点发射导弹
void LaunchMissile(int target_point);

//对指定地点使用机器工人
//若不满足使用条件则返回false
bool UseRobotWorker(Character* user, int target_point);

//对指定地点使用恶魔卡
//若不满足使用条件则返回false
bool UseDevilCard(int target_point);