#ifndef  STAFF_H_
#define  STAFF_H_

class Character;

//��ָ����ɫ���ϼ���Ь
//����ɫ���м���Ь������false
bool SetSpeedShoes(Character* character);

//��ָ����ɫ���Ϸ�Ь
//����ɫ���з�Ь������false
bool SetFlyingShoes(Character* character);

//��ָ����ɫ�����ڹ꿨��Ч��
//�˾ٽ��ݻٽ�ɫ��ԭ������Ь��
//����ɫ�����ڹ꿨״̬������false
bool SetTurtle(Character* character);

//�ݻ�����Ь��
//����ɫ���κ�����Ь�ӣ�����false
bool DestroySpecialShoes(Character* character);
#endif // ! STAFF_H_
