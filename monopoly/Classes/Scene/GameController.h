#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "cocos2d.h"
#include "StorkScene.h"
#include "Character/Character.h"
#include "Scene/MapScene.h"
#include "Character/Dice.h"

USING_NS_CC;

class GameController : public Node
{
public:
	CREATE_FUNC(GameController);
	virtual bool init();

private:
	void addEventListenerCustom();												   //����Զ����¼�������
	void addCharacter(const std::string &name, int tag, int money, int start_pos); //��ӽ�ɫ
	void returnToCharacter(Character *);										   //�ص���ɫ�ӽ�
	void addGoButton();															   //���go��ť
	void startGo();																   //ָ����ǰ��ɫ��ʼ��
	int judgeDirection(int cur_pos);											   //�ж�Ҫ�ߵķ���
	void moveOneStep(int direction);											   //ָ����ǰ��ɫ��ĳ������һ��
	void endGo();																   //MoveOneStep����ǰ���õĺ���
	void backToStand();															   //�ص�վ��״̬����endGo�е���

	Dice *dice_ = nullptr;							 //���汾����Ϸ�������
	MapScene *map_scene_ = nullptr;					 //�����ͼ����
	Vector<Character *> characters_;				 //���汾����Ϸ���н�ɫ��Vector
	EventListenerCustom *listener_custom_ = nullptr; //�Զ����¼��ַ���
	Menu *go_button_menu_ = nullptr;				 //go_button
	StockScene* stock_layer_=nullptr;                      //������г���
	int whose_turn_=0;								 //��¼�ֵ��ڼ�����ɫ�ж�
	int steps_to_go_=0;								 //��¼����Ҫ�߼���
	int steps_has_gone_=0;							 //��¼�������߼���
};
#endif
