#ifndef  STAFF_H_
#define  STAFF_H_

#include "cocos2d.h"
class Character;
USING_NS_CC;

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

//��ָ����ɫʹ��ң������
//����ɫ���غ���ʹ��ң�����ӣ�����false
bool SetControlDice(Character* character, int control_point);

//ָ���ص㷢�䵼��
void LaunchMissile(Character* user, int target_point);

//��ָ���ص�ʹ�û�������
//��������ʹ�������򷵻�false
bool UseRobotWorker(Character* user, int target_point);

//��ָ���ص�ʹ�ö�ħ��
//��������ʹ�������򷵻�false
bool UseDevilCard(int target_point);

bool UseAngelCard(int target_poin);

//������ָ���ص�
bool TransmitGod();

//���ͽ�ɫ��ָ���ص�,����ɫ״̬������������false
bool TransmitCharacter(Character* user, Character* target, int target_point);

//�ݻ�һ��ָ������
//��ָ��λ���޷����򷵻�false
bool UseHouseDestroy(int target_point);

//�������صķ���
//�����ز��ɽ����򷵻�false
bool UseHouseExchange(int house1_pos, int house2_pos);

//ʹ�ù���֤��,ǿ�ƹ���һ�鵱ǰ���������˵�����
//���˵ز��ɹ����Ǯ�������򷵻�false
bool UseHouseBuy(Character* user);

//ʹ�øĽ�֤��
//���˵ز��ɸĽ��򷵻�false
bool UseHouseChange(int target_point);

//ʹ���Ǽۿ�
bool UseRisePriceCard(int target_point);

//ʹ�ú쿨
void UseRedCard(Character* user);

//ʹ�úڿ�
void UseBlackCard(Character* user);

//ʹ�þ�����
//��ָ�������ﲻ�����򷵻�false
bool UseAverageCard(Character* user, Character* target);

//ʹ��ͣ����
//��ָ������״̬�������򷵻�false
bool UseStayCard(Character* target);

//ʹ��ת��
//��ָ������״̬�������򷵻�false
bool UseTurnAroundCard(Character* user);

//ʹ��ǿ�ƶȼٿ��������ж��ֶ�ȥ�ȼ�
void UseHolidayCard(Character* user);
#endif // ! STAFF_H_