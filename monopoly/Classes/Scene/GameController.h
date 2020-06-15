#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "cocos2d.h"
#include "Character/Character.h"
#include "God/God.h"
USING_NS_CC;

class God;
class MapScene;
class Dice;
class StockScene;
class ItemScene;
class GameController : public Node
{
public:
	static GameController* create(std::vector<bool>is_ai)
	{
		auto pRet = new(std::nothrow) GameController();
		if (pRet && pRet->init(is_ai))
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	}
	bool init(std::vector<bool>is_ai);

	void addEventListenerCustom();												   //����Զ����¼�������
	void addCharacter(const std::string& name, int tag, int money, int start_pos, bool is_ai); //��ӽ�ɫ
	void initGod();																   //��ʼ����Ϸ����
	void returnToCharacter(Character *);										   //�ص���ɫ�ӽ�
	void addGoButton();															   //���go��ť
	void startGo();																   //ָ����ǰ��ɫ��ʼ��
	void startRealGo(int steps_to_go);
	int judgeDirection(int cur_pos);											   //�ж�Ҫ�ߵķ���
	void moveOneStep(int direction);											   //ָ����ǰ��ɫ��ĳ������һ��
	void endGo();																   //MoveOneStep����ǰ���õĺ���
	void dealWithGod();
	void dealWithLand();
	void backToStand(Character* character);													   //�ص�վ��״̬����endGo�е���
	void updateGod(int god_type);															   //���������ڵ�ͼ�ϵ�λ��
protected:
	EventListenerTouchOneByOne* listener_block_ = nullptr;
	Dice *dice_ = nullptr;							 //���汾����Ϸ�������
	MapScene *map_scene_ = nullptr;					 //�����ͼ����
	Vector<Character*>characters_;//���汾����Ϸ���н�ɫ��Vector
	Vector<God*>gods_;			  //���汾����Ϸ�������Vector
public:
	Vector<Character*>& getCharacters()
	{
		return characters_;
	}
	Vector<God*>& getGods()
	{
		return gods_;
	}
	Character* getCurCharacter()const
	{
		return characters_.at(whose_turn_);
	}
protected:
	EventListenerCustom *listener_custom_ = nullptr; //�Զ����¼��ַ���
	Menu *go_button_menu_ = nullptr;				 //go_button
	StockScene* stock_layer_=nullptr;                //������г���
	ItemScene* item_layer_ = nullptr;                //������߳���
	int whose_turn_=0;								 //��¼�ֵ��ڼ�����ɫ�ж�
	int steps_to_go_=0;								 //��¼����Ҫ�߼���
	int steps_has_gone_=0;							 //��¼�������߼���
};
#endif
