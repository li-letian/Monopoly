#ifndef  STAFF_H_
#define  STAFF_H_

#include "Character/Character.h"

//��ָ����ɫ����Ħ��
//����ɫ����Ħ�У�����false
bool SetMotor(Character* character);

//��ָ����ɫ���ϳ�
//����ɫ���г�������false
bool SetCar(Character* character);

//�ݻٽ�ͨ����
//����ɫ���κν�ͨ���ߣ�����false
bool DestroyTrafficTool(Character* character);
#endif // ! STAFF_H_
