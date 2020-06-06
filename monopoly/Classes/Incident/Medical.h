#ifndef _MEDICAL_H_
#define _MEDICAL_H_

class Character;
//送进医院
bool SendToHospital(Character* character);
//弹出还有几天出院或者已出院的对话框
void PopUpHospitalDialog(Character* character);

#endif