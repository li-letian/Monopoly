#include <cstdlib>
#include "Scene/GameController.h"
#include "Scene/MapScene.h"
#include "Common/CommonConstant.h"
#include "Land/Land.h"
#include "Land/Hotel.h"
#include "Common/CommonMethod.h"

bool GameController::init()
{
	if (!Node::init())
	{
		return false;
	}
	//����map_scene�������л�
	dice_ = Dice::create(); //��������
	map_scene_ = MapScene::createScene();
	map_scene_->addChild(this, -50);
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
	listener_custom_ = EventListenerCustom::create("monopoly_msg", [=](EventCustom *event) {
		char *buf = static_cast<char *>(event->getUserData());
		int msg = std::atoi(buf); //�����յ�����Ϣ
		switch (msg)
		{
		case (msg_hide_go):												//��go��ť��ʧ
			go_button_menu_->setPosition(visible_size.width + 1000, 0); //����ť�Ƶ���Ļ��
			startGo();													//���￪ʼ��·
			break;
		case (msg_make_go_apper): //��go��ť����
			whose_turn_++;
			if (whose_turn_ >= characters_.size())
			{
				whose_turn_ = 0;
			}
			go_button_menu_->setPosition(Vec2(visible_size.height / 2, visible_size.height / 8));
			returnToCharacter(characters_.at(whose_turn_));

			
			auto character = characters_.at(whose_turn_);
			//�����ﴦ���غ���֮ǰӦ�ô��������

		}
	});
	auto dispatcher = map_scene_->getMap()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener_custom_, map_scene_->getMap());
}

void GameController::addCharacter(const std::string &name, int tag, int money, int start_pos)
{
	auto character = Character::create(name, tag, money, start_pos);
	characters_.pushBack(character);
	character->setPosition(map_scene_->pos(start_pos));
	map_scene_->getMap()->addChild(character, 10);
	log("position: %f %f", character->getPosition().x, character->getPosition().y);
}

void GameController::returnToCharacter(Character *character)
{
	map_scene_->perspectiveJump(map_scene_->pos(character->getCurPos()).x, map_scene_->pos(character->getCurPos()).y);
	//����ĳ�����������任���ӽ�ת����ɫ
}

void GameController::addGoButton()
{
	auto visible_size = Director::getInstance()->getVisibleSize();

	//��ʱû���ҵ��õİ�ť�زģ��Ƚ���ǰ����İ�ť��Ϊͬһ��ͼ
	auto go_button = MenuItemImage::create("go.png", "go.png");
	go_button->setCallback([=](Ref *render) {
		sendMsg(msg_hide_go); //����������ذ�ť����Ϣ
	});
	go_button_menu_ = Menu::create(go_button, NULL);

	//����ê�㡢��ʼλ��
	go_button_menu_->setAnchorPoint(Vec2(0.5f, 0.5f));
	go_button_menu_->setPosition(Vec2(visible_size.height / 2, visible_size.height / 8));

	map_scene_->addChild(go_button_menu_, 11);
}

void GameController::startGo()
{
	//�õ���ǰ���ߵĽ�ɫ
	auto character = characters_.at(whose_turn_);

	//�ӽǻص��ý�ɫ������λ��
	returnToCharacter(character);

	//�����ӵõ�Ҫ�ߵĲ���
	steps_to_go_ = dice_->RollTheDice(character->getStepsScope());
	steps_has_gone_ = 0; //���߲�����0

	int direction = judgeDirection(character->getCurPos());
	moveOneStep(direction);
}

int GameController::judgeDirection(int cur_pos)
{
	int next_pos = cur_pos + 1;
	if (next_pos >= static_cast<int>(map_scene_->totalPosition()))
	{
		next_pos = 0;
	}
	auto cur_x = map_scene_->pos(cur_pos).x;
	auto cur_y = map_scene_->pos(cur_pos).y;
	auto next_x = map_scene_->pos(next_pos).x;
	auto next_y = map_scene_->pos(next_pos).y;
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
	return 0;
}

void GameController::moveOneStep(int direction)
{
	auto character = characters_.at(whose_turn_);
	int next_pos = character->getCurPos() + 1;
	/*if (next_pos >= static_cast<int>(map_scene_->totalPosition()))
	{
		next_pos = 0;
	}*/

	//����
	if (next_pos >= 40)
	{
		next_pos = 0;
	}
	MoveTo *move_to = MoveTo::create(character_one_step_time, map_scene_->pos(next_pos));
	Repeat *repeat = nullptr;
	switch (direction)
	{
	case walk_down:
		repeat = Repeat::create(character->getCharacterAnimDown(), 1);
		break;
	case walk_left:
		repeat = Repeat::create(character->getCharacterAnimLeft(), 1);
		break;
	case walk_right:
		repeat = Repeat::create(character->getCharacterAnimRight(), 1);
		break;
	case walk_up:
		repeat = Repeat::create(character->getCharacterAnimUp(), 1);
		break;
	}
	auto endGoCallBack = CallFunc::create([=]() {
		this->endGo();
	});
	character->setCurPos(next_pos);
	auto spawn_action = Sequence::create(Spawn::create(move_to, repeat, NULL), endGoCallBack, NULL);
	character->runAction(spawn_action);
}

void GameController::endGo()
{
	steps_has_gone_++;
	auto character = characters_.at(whose_turn_);
	if (steps_has_gone_ < steps_to_go_)
	{

		//������Դ���һЩ��·������

		//��������һ��
		auto direction = judgeDirection(character->getCurPos());
		moveOneStep(direction);
	}
	else
	{
		//������ָ���վ��״̬���泯��һ��
		backToStand();
		returnToCharacter(character);
		auto pos = character->getCurPos();

		//���ﴦ��һЩ��½�������

		//���ȵô���һ������

		//Ȼ�����ﴦ����½��λ�ô������¼�
		auto& land = map_scene_->getLand(pos);
		if (!land)
		{
			switch (map_scene_->getType(pos))
			{
			case land_chance:
				break;
			case land_life:
				break;
			case land_hotel:
				land = Hotel::create(map_scene_, pos);
				break;
			case land_business:
				break;
			case land_park:
				break;
			case land_resort:
				break;
			case land_mall:
				break;
			case land_institute:
				break;
			case land_insurance:
				break;
			case land_oil:
				break;
			case land_technology:
				break;
			case land_aviation:
				break;
			case land_hospital:
				break;
			case land_jail:
				break;
			case land_bank:
				break;
			case land_lottery:
				break;
			}
		}
		if (land) land->onLand(character);
		else sendMsg(msg_make_go_apper);
		//������go��ť���³��ֵ���Ϣ �����ڽ���Ϣ���͹��ܷ�װ��
		return;
	}
}

void GameController::backToStand()
{
	auto character = characters_.at(whose_turn_);
	auto name = character->getPlayerName();
	auto direction = judgeDirection(character->getCurPos());
	auto spfcache = SpriteFrameCache::getInstance();
	SpriteFrame *sprite_frame = nullptr;
	switch (direction)
	{
	case walk_down:
		sprite_frame = spfcache->getSpriteFrameByName(StringUtils::format("%s-0.png", name.c_str()));
		character->setSpriteFrame(sprite_frame);
		break;
	case walk_left:
		sprite_frame = spfcache->getSpriteFrameByName(StringUtils::format("%s-4.png", name.c_str()));
		character->setSpriteFrame(sprite_frame);
		break;
	case walk_right:
		sprite_frame = spfcache->getSpriteFrameByName(StringUtils::format("%s-8.png", name.c_str()));
		character->setSpriteFrame(sprite_frame);
		break;
	case walk_up:
		sprite_frame = spfcache->getSpriteFrameByName(StringUtils::format("%s-12.png", name.c_str()));
		character->setSpriteFrame(sprite_frame);
		break;
	}
}