#ifndef  STAFF_H_
#define  STAFF_H_

#include "Character/Character.h"

//给指定角色配上摩托
//若角色已有摩托，返回false
bool SetMotor(Character* character);

//给指定角色配上车
//若角色已有车，返回false
bool SetCar(Character* character);

//摧毁交通工具
//若角色无任何交通工具，返回false
bool DestroyTrafficTool(Character* character);
#endif // ! STAFF_H_
