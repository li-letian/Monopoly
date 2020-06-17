#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
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
	static GameController* create(std::vector<bool>is_ai);
	bool init(std::vector<bool>is_ai);

	void addGoButton();							//���go��ť
	void returnToCharacter(Character *);		//�ص���ɫ�ӽ�
	void startRealGo(int steps_to_go);			//ָ����ǰ��ɫ������ʼ��
	int judgeDirection(int cur_pos);			//�ж�Ҫ�ߵķ���
	void moveOneStep(int direction);			//ָ����ǰ��ɫ��ĳ������һ��
	void endGo();								//��һ���������ж�Ҫִ��ʲô����
	void dealWithGod();							//���߽�������God
	void dealWithLand();						//���߽�������Land
	void backToStand(Character* character);		//ʹָ����ɫ�ص���ȷ��վ������
	void updateGod(int god_type);				//���������ڵ�ͼ�ϵ�λ��

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

private:
	void music_open();								 //��bgm
	void music_close();								 //�ر�bgm
	void addEventListenerCustom();					 //����Զ����¼�������
	//��ӽ�ɫ
	void addCharacter(const std::string& name, int tag, int money, int start_pos, bool is_ai);
	void initGod();									 //��ʼ����Ϸ����
	void ReadyToStartGo();							 //ָ����ǰ��ɫ׼����ʼ��

	EventListenerTouchOneByOne* listener_block_ = nullptr;
	Dice* dice_ = nullptr;							 //���汾����Ϸ�������
	MapScene* map_scene_ = nullptr;					 //�����ͼ����
	Vector<Character*>characters_;					 //���汾����Ϸ���н�ɫ��Vector
	Vector<God*>gods_;								 //���汾����Ϸ�������Vector

	EventListenerCustom *listener_custom_ = nullptr; //�Զ����¼��ַ���
	StockScene* stock_layer_=nullptr;                //������г���
	ItemScene* item_layer_ = nullptr;                //������߳���
	int whose_turn_=0;								 //��¼�ֵ��ڼ�����ɫ�ж�
	int steps_to_go_=0;								 //��¼����Ҫ�߼���
	int steps_has_gone_=0;							 //��¼�������߼���
};
#endif
