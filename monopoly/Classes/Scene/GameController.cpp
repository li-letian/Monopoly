#include <cstdlib>

#include "Scene/GameController.h"
#include "Scene/MapScene.h"
#include "Common/CommonConstant.h"
#include "StorkScene.h"
#include "Land/Business.h"
#include "Land/Hotel.h"
#include "Land/Jail.h"
#include "Land/Hospital.h"
#include "Land/Insurance.h"
#include "Land/Aviation.h"
#include "Land/Oil.h"
#include "Land/Technology.h"


#include "Incident/Incident.h"

#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"

bool GameController::init()
{
	if (!Node::init())
	{
		return false;
	}
	//创造map_scene场景并切换
	dice_ = Dice::create(); //创造骰子
	map_scene_ = MapScene::createScene();
	map_scene_->addChild(this, -50,"game_controller");
	stock_layer_ = StockScene::createScene(map_scene_); //初始化stock
	
	
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, map_scene_, Color3B(0, 255, 255)));

	//添加自定义事件监听器
	addEventListenerCustom();

	//添加角色，暂时固定添加2个:初音未来与南小鸟
	addCharacter("miku", miku, 15000, start_position);
	addCharacter("nanxiaoniao", nanxiaoniao, 15000, start_position+1);

	whose_turn_ = 0;
	returnToCharacter(characters_.at(whose_turn_)); //回到第一个角色的视角
	addGoButton();									//添加go按钮
	stock_layer_->remakeLabel(characters_.at(whose_turn_));
	map_scene_->setInfoOnDisplay(characters_.at(whose_turn_));
	map_scene_->updateInformation(characters_.at(whose_turn_));
	return true;
}

void GameController::addEventListenerCustom()
{
	auto visible_size = Director::getInstance()->getVisibleSize();
	listener_custom_ = EventListenerCustom::create("monopoly_msg", [=](EventCustom *event) {
		char *buf = static_cast<char *>(event->getUserData());
		int msg = std::atoi(buf); //解析收到的信息
		switch (msg)
		{
		case (msg_hide_go):												//让go按钮消失
			go_button_menu_->setPosition(visible_size.width + 1000, 0); //将按钮移到屏幕外
			startGo();													//人物开始走路
			break;
		case (msg_make_go_apper): //让go按钮出现
			auto func = [=]() {

				whose_turn_++;
				if (whose_turn_ >= characters_.size())
				{
					whose_turn_ = 0;
				}

				auto character = characters_.at(whose_turn_);

				stock_layer_->stockUpdate();
				stock_layer_->remakeLabel(character);
				map_scene_->setInfoOnDisplay(character);
				map_scene_->updateInformation(character);

				//在这里处理本回合走之前应该处理的事情
				returnToCharacter(character);

				//在后面添加回合开始前要做的事

				//1.先判断人物状态
				switch (character->getCondition())
				{
				case normal:
					if (character->getInsurance() > 0)
						character->setInsurance(character->getInsurance() - 1);
					go_button_menu_->setPosition(Vec2(visible_size.height / 2, visible_size.height / 8));
					break;
				case in_jail:
					character->setStopTimes(character->getStopTimes() - 1);
					PopUpJailDialog(character, map_scene_);
					break;
				case on_holiday:
					character->setStopTimes(character->getStopTimes() - 1);
					PopUpHolidayDialog(character, map_scene_);
					break;
				case in_hospital:
					character->setStopTimes(character->getStopTimes() - 1);
					PopUpHospitalDialog(character, map_scene_);
					break;
				}
			};
			auto seq = Sequence::create(DelayTime::create(0.3f), CallFunc::create(func), nullptr);
			if (characters_.at(whose_turn_)->getMoney() < 0)
			{
				auto character = characters_.at(whose_turn_);
				auto pop = PopUpLayer::create();
				pop->setTitle("破产");
				auto text = StringUtils::format("%s", character->getPlayerName())
					+ std::string("已破产");
				pop->setContent(text);
				pop->setCallBack([=](Ref* render) {
					characters_.erase(whose_turn_);
					whose_turn_--;
					character->removeFromParentAndCleanup(true);
					this->runAction(seq);
					});
				pop->setOnScene();
			}
			else
			{
				this->runAction(seq);
			}
			break;
		}
	});
	auto dispatcher = map_scene_->getMap()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener_custom_, map_scene_->getMap());
}

void GameController::addCharacter(const std::string &name, int tag, int money, int start_pos)
{
	auto character = Character::create(name, tag, money, start_pos,map_scene_);
	characters_.pushBack(character);
	character->setPosition(map_scene_->pos(start_pos));
	map_scene_->getMap()->addChild(character, 10,tag);
	log("position: %f %f", character->getPosition().x, character->getPosition().y);
}

void GameController::returnToCharacter(Character *character)
{
	map_scene_->perspectiveJump(map_scene_->pos(character->getCurPos()).x, map_scene_->pos(character->getCurPos()).y);
	//经过某种神奇的坐标变换将视角转到角色
}

void GameController::addGoButton()
{
	auto visible_size = Director::getInstance()->getVisibleSize();

	//暂时没有找到好的按钮素材，先将按前按后的按钮设为同一张图
	auto go_button = MenuItemImage::create("go.png", "go.png");
	go_button->setCallback([=](Ref *render) {
		sendMsg(msg_hide_go); //点击后发送隐藏按钮的信息
	});
	go_button_menu_ = Menu::create(go_button, NULL);

	//设置锚点、初始位置
	go_button_menu_->setAnchorPoint(Vec2(0.5f, 0.5f));
	go_button_menu_->setPosition(Vec2(visible_size.height / 2, visible_size.height / 8));

	map_scene_->addChild(go_button_menu_, 11);
}

void GameController::startGo()
{
	//得到当前该走的角色
	auto character = characters_.at(whose_turn_);

	//视角回到该角色的所在位置
	returnToCharacter(character);

	//掷骰子得到要走的步数
	steps_to_go_ = dice_->RollTheDice(character->getStepsScope());
	if (character->getStepsScope() == turtle_steps)
	{
		character->setTurtleTimes(character->getTurtleTimes() - 1);
	}
	if (character->getTurtleTimes() == 0)
	{
		character->setStepsScope(walk_steps);
	}
	steps_has_gone_ = 0; //已走步数置0

	int direction = judgeDirection(character->getCurPos());
	moveOneStep(direction);
}

int GameController::judgeDirection(int cur_pos)
{
	int next_pos = cur_pos + 1;
	if (next_pos >= static_cast<int>(map_scene_->totalPosition()))
	{
		next_pos = start_position;
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
	//if (next_pos >= static_cast<int>(map_scene_->totalPosition()))
	if (next_pos >= total_position)
	{
		next_pos = start_position;
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

		//这里可以处理一些过路的事情

		//继续走下一步
		auto direction = judgeDirection(character->getCurPos());
		moveOneStep(direction);
	}
	else
	{
		//让人物恢复到站立状态，面朝下一格
		backToStand();
		returnToCharacter(character);
		auto pos = character->getCurPos();

		//这里处理一些着陆后的事情

		//首先得处理一下神灵

		//然后这里处理着陆到位置触发的事件
		auto &land = map_scene_->getLand(pos);
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
				land = Business::create(map_scene_, pos);
				break;
			case land_insurance:
				land= Insurance::create(map_scene_, pos);
				break;
			case land_oil:
				land = Oil::create(map_scene_, pos);
				break;
			case land_technology:
				land= Technology::create(map_scene_, pos);
				break;
			case land_aviation:
				land = Aviation::create(map_scene_, pos);
				break;
			case land_hospital:
				land = Hospital::create(map_scene_, pos);
				break;
			case land_jail:
				land = Jail::create(map_scene_, pos);
				break;
			case land_bank:
				break;
			case land_lottery:
				break;
			}
		}
		if (land)
			land->onLand(character);
		else
			sendMsg(msg_make_go_apper);

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
