#ifndef _CHRIMINAL_H_
#define _CHRIMINAL_H_

#include "cocos2d.h"
USING_NS_CC;
class Character;

//�͵�����
bool SendToJail(Character* character);

//�������м�����������ѳ����ĶԻ���
void PopUpJailDialog(Character* character);

#endif