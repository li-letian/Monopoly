#include <cstdlib>

#include "Scene/GameController.h"
#include "Scene/MapScene.h"
#include "Scene/ItemScene.h"
#include "Scene/StockScene.h"

#include "Character/Character.h"
#include "Character/Dice.h"

#include "Land/Business.h"
#include "Land/Hotel.h"
#include "Land/Jail.h"
#include "Land/Hospital.h"
#include "Land/Insurance.h"
#include "Land/Aviation.h"
#include "Land/Oil.h"
#include "Land/Technology.h"
#include "Land/Bank.h"
#include "Land/Life.h"
#include "Land/Chance.h"
#include "Incident/Incident.h"
#include "Incident/Stay.h"

#include "God/God.h"
#include "God/Angel.h"
#include "God/Devil.h"
#include "God/Earth.h"
#include "God/Luck.h"
#include "God/Poor.h"
#include "God/Rich.h"
#include "God/Unluck.h"

#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"

#include "AudioEngine.h"

void GameController::music_open()
{
	auto bgm_sound = AudioEngine::play2d("BGM.mp3", true);
	AudioEngine::setVolume(bgm_sound, 0.4f);
	map_scene_->setMenuCallback("setting", [=](Ref* ref) {music_close(); });
}


void GameController::music_close()
{
	AudioEngine::stopAll();
	map_scene_->setMenuCallback("setting", [=](Ref* ref) {music_open(); });
}

bool GameController::init(std::vector<bool> is_ai)
{
	if (!Node::init())
	{
		return false;
	}
	whose_turn_ = 0;
	//创建一个骰子

	dice_ = Dice::create();
	this->addChild(dynamic_cast<Node*>(dice_), 50);
	//创建map_scene、stock_scene
	map_scene_ = MapScene::createScene();
	map_scene_->addChild(this, 500, "game_controller");
	stock_layer_ = StockScene::createScene(map_scene_);
	//将当前场景替换为map_scene
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, map_scene_, Color3B(0, 255, 255)));

	map_scene_->setMenuCallback("setting", [=](Ref* ref) {music_close(); });

	//添加自定义事件监听器
	addEventListenerCustom();

	//添加角色
	addCharacter("miku", 1, initial_money, 0, is_ai[1]);
	addCharacter("nanxiaoniao", 2, initial_money, 71, is_ai[2]);
	addCharacter("jingtian", 3, initial_money, 149, is_ai[3]);
	addCharacter("luff", 4, initial_money, 224, is_ai[4]);
	addCharacter("usagi", 5, initial_money, 293, is_ai[5]);
	addCharacter("iori", 6, initial_money, 394, is_ai[6]);

	//初始化神
	initGod();

	//创建item_scene
	item_layer_ = ItemScene::createScene(map_scene_, this);

	//回到第一个角色的位置
	returnToCharacter(characters_.at(whose_turn_));
	//添加Go button
	addGoButton();

	//更新一些东西
	stock_layer_->remakeLabel(characters_.at(whose_turn_));
	map_scene_->setInfoOnDisplay(characters_.at(whose_turn_));
	map_scene_->updateInformation(characters_.at(whose_turn_));

	for (auto character : characters_)
	{
		for (int i = 1; i <= 6; i++)
		{
			GetRandomItem(character, item_layer_);
		}
	}
	item_layer_->updateMenu(characters_.at(whose_turn_));
	return true;
}

void GameController::addEventListenerCustom()
{
	auto visible_size = Director::getInstance()->getVisibleSize();
	listener_custom_ = EventListenerCustom::create("monopoly_msg", [=](EventCustom *event) {
		//解析收到的信息
		char *buf = static_cast<char *>(event->getUserData());
		int msg = std::atoi(buf);
		switch (msg)
		{
			//当前人物开始走
		case (msg_start_go):
			go_button_menu_->setPosition(visible_size.width + 1000, 0);

			listener_block_->setEnabled(true);



			startGo();
			break;
			//当前人物回合结束，轮到下个人走
		case (msg_make_go_apper):
		{
			//func函数将在一段时间后执行
			characters_.at(whose_turn_)->setMiniAvatar(characters_.at(whose_turn_)->getCurPos());
			listener_block_->setEnabled(true);
			auto func = [=]() {
				//定位到下一个角色
				whose_turn_++;
				if (whose_turn_ >= characters_.size())
				{
					whose_turn_ = 0;
					map_scene_->updateDay();
					stock_layer_->stockUpdate();

					for (auto c : characters_)
					{
						c->setLoan(static_cast<int>(c->getLoan() * 1.03f));
						c->setDeposit(static_cast<int>(c->getDeposit() * 1.03f));
					}

				}

				//找到当前角色
				auto character = characters_.at(whose_turn_);

				if (character->getGodPossessed() != normal)
				{
					character->setGodTimes(character->getGodTimes() - 1);
					if (character->getGodTimes() <= 0)
					{
						character->setGodPossessed(normal);
						gods_.pushBack(dynamic_cast<God *>(character->getChildByName("god")));
						character->removeChildByName("god", true);
						updateGod(no_god);
					}
				}

				//更新一些信息
				stock_layer_->remakeLabel(character);
				map_scene_->setInfoOnDisplay(character);
				map_scene_->updateInformation(character);
				item_layer_->updateMenu(characters_.at(whose_turn_));

				//回到当前人物视角
				returnToCharacter(character);

				listener_block_->setEnabled(false);
				//判断人物状态
				switch (character->getCondition())
				{
				case normal:
					if (character->getInsurance() > 0)
						character->setInsurance(character->getInsurance() - 1);
					if (character->getIsAI())
					{
						listener_block_->setEnabled(true);
						startGo();
					}
					else
					{
						go_button_menu_->setPosition(Vec2(visible_size.height / 2, visible_size.height / 8));
					}
					break;
				case in_jail:
					character->setStopTimes(character->getStopTimes() - 1);
					PopUpJailDialog(character);
					break;
				case on_holiday:
					character->setStopTimes(character->getStopTimes() - 1);
					PopUpHolidayDialog(character);
					break;
				case in_hospital:
					character->setStopTimes(character->getStopTimes() - 1);
					PopUpHospitalDialog(character);
					break;
				}
				
			};
			auto seq = Sequence::create(DelayTime::create(0.5f), CallFunc::create(func), nullptr);

			//破产
			if (characters_.at(whose_turn_)->getMoney() < 0)
			{
				auto character = characters_.at(whose_turn_);
				auto pop = PopUpLayer::create();
				pop->setTitle("破产");
				auto text = character->getPlayerName() + std::string("已破产");
				pop->setContent(text);
				pop->setCallBack([=](Ref *render) {
					characters_.erase(whose_turn_);
					whose_turn_--;
					character->removeFromParent();
					this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create(func), nullptr));
				});
				pop->setOnScene();
			}
			else
			{
				this->runAction(seq);
			}
			break;
		}
		//只将GoButton隐藏
		//通常道具使用时才会发送这个消息
		case msg_hide_go_only:
			go_button_menu_->setPosition(visible_size.width + 1000, 0);
			steps_to_go_ = 0;
			steps_has_gone_ = 0;
			break;
		}
	});
	listener_block_ = EventListenerTouchOneByOne::create();
	listener_block_->setSwallowTouches(true);
	listener_block_->setEnabled(false);
	listener_block_->onTouchBegan = [=](Touch* touch,Event *event)
	{
		return true;
	};

	auto dispatcher = map_scene_->getMap()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener_custom_, map_scene_->getMap());
	dispatcher->addEventListenerWithSceneGraphPriority(listener_block_, this);
}

void GameController::addCharacter(const std::string &name, int tag, int money, int start_pos, bool is_ai)
{
	auto character = Character::create(name, tag, money, start_pos, map_scene_);
	character->setIsAI(is_ai);
	characters_.pushBack(character);
	character->setPosition(map_scene_->pos(start_pos));
	map_scene_->getMap()->addChild(character, 10, tag);
	backToStand(character);
	log("position: %f %f", character->getPosition().x, character->getPosition().y);
}

void GameController::returnToCharacter(Character *character)
{
	map_scene_->perspectiveJump(map_scene_->pos(character->getCurPos()).x, map_scene_->pos(character->getCurPos()).y);
}

void GameController::addGoButton()
{
	auto visible_size = Director::getInstance()->getVisibleSize();

	auto go_button = MenuItemImage::create("go.png", "go.png");
	go_button->setCallback([=](Ref *render) {
		auto sound_effect = AudioEngine::play2d("bottom_down.mp3", false);
		SendMsg(msg_start_go);
	});
	go_button_menu_ = Menu::create(go_button, NULL);

	go_button_menu_->setAnchorPoint(Vec2(0.5f, 0.5f));
	go_button_menu_->setPosition(Vec2(visible_size.height / 2, visible_size.height / 8));

	map_scene_->addChild(go_button_menu_, 11);
}

void GameController::startGo()
{
	auto character = characters_.at(whose_turn_);

	returnToCharacter(character);

	//对于停留卡的判断
	if (character->getIsStay() == true)
	{
		steps_to_go_ = 0;
		steps_has_gone_ = 0;
		character->setIsStay(false);
		auto endGoCallFunc = CallFunc::create([=]() {
			this->endGo();
		});
		auto sequence = Sequence::create(DelayTime::create(0.5f), endGoCallFunc, nullptr);
		this->runAction(sequence);
	}
	else
	{
		//对于乌龟卡的判断
		if (character->getStepsScope() == turtle_steps)
		{
			character->setTurtleTimes(character->getTurtleTimes() - 1);
			if (character->getTurtleTimes() == 0)
			{
				character->setStepsScope(walk_steps);
			}
		}

		//掷骰子
		if (character->getIsAI())
		{
			auto rollDiceCallFunc = CallFunc::create([=]() {
				dice_->RollTheDice(character->getStepsScope(), character);
				});
			auto sequence = Sequence::create(DelayTime::create(0.5f), rollDiceCallFunc, nullptr);
			this->runAction(sequence);
		}
		else
		{
			dice_->RollTheDice(character->getStepsScope(), character);
		}
	}
}

void GameController::startRealGo(int steps_to_go)
{
	auto character = characters_.at(whose_turn_);
	steps_to_go_ = steps_to_go;
	steps_has_gone_ = 0;

	int direction = judgeDirection(character->getCurPos());
	moveOneStep(direction);
}

int GameController::judgeDirection(int cur_pos)
{
	auto character = characters_.at(whose_turn_);
	int next_pos = cur_pos + character->getTowardDirection();
	if (next_pos >= map_scene_->totalPosition())
	{
		next_pos = 0;
	}
	else if (next_pos < start_position)
	{
		next_pos = map_scene_->totalPosition() - 1;
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
	listener_block_->setEnabled(true);
	auto character = characters_.at(whose_turn_);
	int next_pos = character->getCurPos() + character->getTowardDirection();
	if (next_pos >= total_position)
	{
		next_pos = start_position;
	}
	if (next_pos < start_position)
	{
		next_pos = total_position - 1;
	}
	MoveTo *character_move_to = MoveTo::create(character_one_step_time, map_scene_->pos(next_pos));
	MoveBy* map_move_by = MoveBy::create(character_one_step_time, map_scene_->pos(character->getCurPos()) - map_scene_->pos(next_pos));
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
		dice_->decreaseNumber();
		this->endGo();
	});
	character->setCurPos(next_pos);
	auto spawn_action = Sequence::create(Spawn::create(character_move_to, repeat, NULL), endGoCallBack, NULL);
	character->runAction(spawn_action);
	map_scene_->getMap()->runAction(map_move_by);
	character->setMiniAvatar(character->getCurPos());
}

void GameController::endGo()
{
	listener_block_->setEnabled(false);
	steps_has_gone_++;
	auto character = characters_.at(whose_turn_);
	if (steps_has_gone_ < steps_to_go_)
	{

		auto pos = character->getCurPos();
		auto &land = map_scene_->getLand(pos);
		if (map_scene_->getType(pos) == land_bank)
		{
			
			if (!land)
				land = Bank::create(pos);
			land->byLand(character);
		}
		else
		{
			auto direction = judgeDirection(pos);
			moveOneStep(direction);
		}
	}
	else
	{
		backToStand(character);
		returnToCharacter(character);
		dealWithGod();

		return;
	}
}

void GameController::dealWithGod()
{
	auto character = characters_.at(whose_turn_);
	auto pos = character->getCurPos();
	auto god = map_scene_->getGod(pos);
	if (god)
		god->onLand(character);
	else
		dealWithLand();
}

void GameController::dealWithLand()
{
	auto character = characters_.at(whose_turn_);
	auto pos = character->getCurPos();
	auto &land = map_scene_->getLand(pos);
	if (!land)
	{
		switch (map_scene_->getType(pos))
		{
		case land_chance:
			land = Chance::create(pos);
			break;
		case land_life:
			land = Life::create(pos);
			break;
		case land_hotel:
			land = Hotel::create(pos);
			break;
		case land_business:
			land = Business::create(pos);
			break;
		case land_insurance:
			land = Insurance::create(pos);
			break;
		case land_oil:
			land = Oil::create(pos);
			break;
		case land_technology:
			land = Technology::create(pos);
			break;
		case land_aviation:
			land = Aviation::create(pos);
			break;
		case land_hospital:
			land = Hospital::create(pos);
			break;
		case land_jail:
			land = Jail::create(pos);
			break;
		case land_bank:
			land = Bank::create(pos);
			break;
		case land_lottery:
			break;
		}
	}
	if (land)
		land->onLand(character);
	else
		SendMsg(msg_make_go_apper);
}

void GameController::backToStand(Character *character)
{
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
	character->setMiniAvatar(character->getCurPos());
}

void GameController::initGod()
{
	gods_.pushBack(Angel::create());
	gods_.pushBack(Devil::create());
	gods_.pushBack(Earth::create());
	gods_.pushBack(Luck::create());
	gods_.pushBack(Poor::create());
	gods_.pushBack(Rich::create());
	gods_.pushBack(Unluck::create());
	for (auto god : gods_)
	{
		map_scene_->getMap()->addChild(god, 10);
	}
	updateGod(no_god);
}

void GameController::updateGod(int god_type)
{
	for (int i = 0; i < gods_.size(); i++)
	{
		auto god = gods_.at(i);
		if (god->getTag() == god_type)
		{
			gods_.erase(i);
			i--;
		}
		else
		{
			while (god->setPos(start_position + Dice::getARandomNumber(total_position - start_position), map_scene_) != true)
			{
				;
			}
		}
	}
}