#ifndef  STAFF_H_
#define  STAFF_H_

#include "cocos2d.h"
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

//��ָ����ɫʹ��ң������
//����ɫ���غ���ʹ��ң�����ӣ�����false
bool SetControlDice(Character* character, int control_point);

//ָ���ص㷢�䵼��
void LaunchMissile(int target_point);

//��ָ���ص�ʹ�û�������
//��������ʹ�������򷵻�false
bool UseRobotWorker(Character* user, int target_point);

//��ָ���ص�ʹ�ö�ħ��
//��������ʹ�������򷵻�false
bool UseDevilCard(int target_point);

//������ָ���ص�
void TransmitGod();

//���ͽ�ɫ��ָ���ص�
void TransmitCharacter(Character* user, Character* target, int target_point);

//�ݻ�һ��ָ������
//��ָ��λ���޷����򷵻�false
bool UseHouseDestroy(int target_point);

//�������صķ���
//�����ز��ɽ����򷵻�false
bool UseHouseExchange(int house1_pos, int house2_pos);

//ʹ�ù���֤��
//���˵ز��ɹ����򷵻�false
bool UseHouseBuy(Character* user, int target_point);