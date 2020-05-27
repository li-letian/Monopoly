#include <cstdlib>
#include "Scene/GameController.h"
#include "Scene/MapScene.h"
#include "Common/CommonConstant.h"

GameController::GameController()
	:map_scene_(NULL)
{

}

GameController::~GameController()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener_custom_);
}

bool GameController::init()
{
	if (!Node::init())
	{
		return false;
	}
	//����map_scene�������л�
	dice_ = Dice::create();
	map_scene_ = MapScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, map_scene_, Color3B(0, 255, 255)));
	
	//����Զ����¼�������
	addEventListenerCustom();
	
	//��ӽ�ɫ����ʱ�̶����2��:����δ������С��
	addCharacter("miku", miku, 15000, 0);
	addCharacter("nanxiaoniao", nanxiaoniao, 15000, 1);
	
	whose_turn_ = 0;
	returnToCharacter(characters_.at(whose_turn_)); //�ص���һ����ɫ���ӽ�
	addGoButton();									//���go��ť

	
	return true;
}

void GameController::addEventListenerCustom()
{
	auto visible_size = Director::getInstance()->getVisibleSize();
	listener_custom_ = EventListenerCustom::create("monopoly_msg", [=](EventCustom* event) {
		char* buf = static_cast<char*>(event->getUserData());
		int msg = std::atoi(buf);
		switch (msg)
		{
		case(msg_hide_go): //��go��ť��ʧ
			go_button_menu_->setPosition(visible_size.width + 1000, 0); //����ť�Ƶ���Ļ��
			StartGo();		//���￪ʼ��·
			break;
		case(msg_make_go_apper):	//��go��ť����
			whose_turn_++;
			if (whose_turn_ >= characters_.size());
			{
				whose_turn_ = 0;
			}
			go_button_menu_->setPosition(Vec2(visible_size.width / 2, 3 * visible_size.height / 4));
			returnToCharacter(characters_.at(whose_turn_));
		}
		});
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithFixedPriority(listener_custom_, 1);
}

void GameController::addCharacter(const std::string&name,int tag,int money,int start_pos)
{
	auto character = Character::create(name, tag, money, start_pos);
	characters_.push_back(character);
	character->setPosition(map_scene_->pos_.at(start_pos));
	map_scene_->map_->addChild(character,10);
}

void GameController::returnToCharacter(Character* character)
{
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto tile_size = map_scene_->map_->getTileSize();

	//����ĳ�����������任���ӽ�ת����ɫ
	map_scene_->map_->setPosition(
		Vec2(-map_scene_->pos_.at(character->getCurPos()).x + visible_size.width / 2,
			tile_size.height * static_cast<float>(100) - map_scene_->pos_.at(character->getCurPos()).y + visible_size.height / 2));
}

void GameController::addGoButton()
{
	auto visible_size = Director::getInstance()->getVisibleSize();

	//��ʱû���ҵ��õİ�ť�زģ��Ƚ���ǰ����İ�ť��Ϊͬһ��ͼ
	auto go_button = MenuItemImage::create("go.png", "go.png");
	go_button->setCallback([=](Ref* render) {
		//����������ذ�ť����Ϣ
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		char* buf = new char[10];
		sprintf(buf, "%d", msg_hide_go);
		EventCustom event = EventCustom("monopoly_msg");
		event.setUserData(buf);
		dispatcher->dispatchEvent(&event);
		CC_SAFE_DELETE_ARRAY(buf);
		});
	go_button_menu_ = Menu::create(go_button, NULL);

	//����ê�㡢��ʼλ��
	go_button_menu_->setAnchorPoint(Vec2(0.5f, 0.5f));
	go_button_menu_->setPosition(Vec2(visible_size.width / 2, 3 * visible_size.height / 4));

	map_scene_->addChild(go_button_menu_, 11);
}

void GameController::StartGo()
{
	//�õ���ǰ���ߵĽ�ɫ
	auto character = characters_.at(whose_turn_);

	//�ӽǻص��ý�ɫ������λ��
	returnToCharacter(character);

	//�����ӵõ�Ҫ�ߵĲ���
	steps_to_go_ = dice_->RollTheDice(character->getStepsScope());
	steps_has_gone_ = 0;		//���߲�����0

	int direction = JudgeDirection(character->getCurPos());
	MoveOneStep(direction);
}

int GameController::JudgeDirection(int cur_pos)
{
	int cur_x = map_scene_->pos_.at(cur_pos).x;
	int cur_y = map_scene_->pos_.at(cur_pos).y;
	int next_x = map_scene_->pos_.at(cur_pos + 1).x;
	int next_y = map_scene_->pos_.at(cur_pos + 1).y;
	if (next_y < cur_y)
	{
		return walk_down;
	}
	else if (next_x < cur_x)
	{
		return walk_left;
	}
	else if (next_x > cur_x)
	{
		return walk_right;
	}
	else if (next_y > cur_y)
	{
		return walk_up;
	}
}

void GameController::MoveOneStep(int direction)
{
	auto character = characters_.at(whose_turn_);
	MoveBy* move_by;
	Repeat* repeat;
	switch (direction)
	{
	case walk_down:
		move_by = MoveBy::create(character_one_step_time, Vec2(0, -tile_size));
		repeat = Repeat::create(character->getCharacterAnimDown(),1);
		break;
	case walk_left:
		move_by = MoveBy::create(character_one_step_time, Vec2(-tile_size, 0));
		repeat = Repeat::create(character->getCharacterAnimLeft(), 1);
		break;
	case walk_right:
		move_by = MoveBy::create(character_one_step_time, Vec2(tile_size, 0));
		repeat = Repeat::create(character->getCharacterAnimRight(), 1);
		break;
	case walk_up:
		move_by = MoveBy::create(character_one_step_time, Vec2(0, tile_size));
		repeat = Repeat::create(character->getCharacterAnimUp(), 1);
		break;
	}
	auto endGoCallBack = [=]() {
		this->endGo();
	};
	auto spawn_action = Sequence::create(Spawn::create(move_by, repeat, NULL), endGoCallBack, NULL);
	character->runAction(spawn_action);
}

void GameController:: endGo()
{
	steps_has_gone_++;
	auto character = characters_.at(whose_turn_);
	if (steps_has_gone_ < steps_to_go_)
	{
		character->setCurPos(character->getCurPos() + 1);
		steps_has_gone_++;
		auto direction = JudgeDirection(character->getCurPos());
		MoveOneStep(direction);
	}
	else
	{
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		char* buf = new char[10];
		sprintf(buf, "%d", msg_make_go_apper);

		EventCustom event("monopoly_msg");
		event.setUserData(buf);
		dispatcher->dispatchEvent(&event);
		CC_SAFE_DELETE_ARRAY(buf);
		return;
	}
}
