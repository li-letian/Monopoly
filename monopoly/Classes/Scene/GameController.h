#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "cocos2d.h"
#include "Character/Character.h"
#include "Scene/MapScene.h"
#include "Character/Dice.h"
USING_NS_CC;

class GameController : public Node {
public:
	GameController();
	~GameController();
	
	CREATE_FUNC(GameController);
	virtual bool init();
private:
	void addEventListenerCustom();			//����Զ����¼�������
	void addCharacter(const std::string& name, int tag, int money,int start_pos);//��ӽ�ɫ
	void returnToCharacter(Character*);		//�ص���ɫ�ӽ�
	void addGoButton();						//���go��ť
	void StartGo();							//ָ����ǰ��ɫ��ʼ��
	int JudgeDirection(int cur_pos);		//�ж�Ҫ�ߵķ���
	void MoveOneStep(int direction);		//ָ����ǰ��ɫ��ĳ������һ��
	void endGo();							//MoveOneStep����ǰ���õĺ���

	Dice* dice_;							//���汾����Ϸ�������
	MapScene* map_scene_;					//�����ͼ����
	std::vector<Character*>characters_;		//���汾����Ϸ���н�ɫ��Vector
	EventListenerCustom* listener_custom_;  //�Զ����¼��ַ���
	Menu* go_button_menu_;					//go_button
	int whose_turn_;						//��¼�ֵ��ڼ�����ɫ�ж�
	int steps_to_go_;						//��¼����Ҫ�߼���
	int steps_has_gone_;					//��¼�������߼���
};
#endif
