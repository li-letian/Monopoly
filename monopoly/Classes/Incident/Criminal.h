#ifndef _CHRIMINAL_H_
#define _CHRIMINAL_H_

#include "cocos2d.h"
USING_NS_CC;
class Character;

//送到监狱
bool SendToJail(Character* character);

//弹出还有几天出狱或者已出狱的对话框
void PopUpJailDialog(Character* character);

#endif