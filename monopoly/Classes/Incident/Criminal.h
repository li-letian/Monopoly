#ifndef _CHRIMINAL_H_
#define _CHRIMINAL_H_

class Character;

//送到监狱
bool SendToJail(Character* character);

//弹出还有几天出狱或者已出狱的对话框
void PopUpJailDialog(Character* character);

#endif