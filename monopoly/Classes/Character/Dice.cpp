#include <ctime>
#include "Character/Dice.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "AudioEngine.h"

bool Dice::init()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	return true;
}

void Dice::RollTheDice(int steps_scope,Character*character)
{
	cur_point_ = 1;
	if (character->getControlDicePoint() > 0)
	{
		steps_ = character->getControlDicePoint();
		character->setControlDicePoint(0);
	}
	else
	{
		steps_ = random(steps_scope) + 1;
	}
	dice_change_time_ = 0.1f;
	if (walk_steps < steps_ && steps_<= speed_steps)
	{
		dice_change_time_ = 0.05f;
	}
	else if (speed_steps < steps_ && steps_ <= flying_steps)
	{
		dice_change_time_ = 0.025f;
	}
	increaseNumber();
}

int Dice::getARandomNumber(int scope)
{
	return random(scope);
}

void Dice::increaseNumber()
{
	auto soundEffectID = AudioEngine::play2d("bottom_up.mp3", false);
	auto map_scene = GetMapScene();
	showCurNumber();
	auto endAppearCallFunc = CallFunc::create([=]() {
		this->endAppear();
		});
	auto sequence = Sequence::create(DelayTime::create(dice_change_time_), endAppearCallFunc, nullptr);
	map_scene->runAction(sequence);
}

void Dice::endAppear()
{
	auto map_scene = GetMapScene();
	cur_point_++;
	if (cur_point_ > steps_)
	{
		cur_point_--;
		auto game_controller = GetGameController();
		auto startRealGoCallFunc = CallFunc::create([=]() {
			game_controller->startRealGo(steps_);
			});
		auto sequence = Sequence::create(DelayTime::create(dice_stay_time), startRealGoCallFunc, nullptr);
		map_scene->runAction(sequence);
	}
	else
	{
		map_scene->removeChildByName(StringUtils::format("number_%d", cur_point_-1), true);
		increaseNumber();
	}
}

void Dice::decreaseNumber()
{
	auto soundEffectID = AudioEngine::play2d("bottom_up.mp3", false);
	auto map_scene = GetMapScene();
	map_scene->removeChildByName(StringUtils::format("number_%d", cur_point_), true);
	cur_point_--;
	if (cur_point_ != 0)
	{
		showCurNumber();
	}
}

void Dice::showCurNumber()
{
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto number = Label::createWithSystemFont(StringUtils::format("%d", cur_point_), "»ªÎÄçúçê", 70);
	number->setColor(Color3B(0, 0, 0));
	number->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	number->setPosition(Vec2(visible_size.height / 2, visible_size.height / 8));
	auto map_scene = GetMapScene();
	map_scene->addChild(number, 11, StringUtils::format("number_%d", cur_point_));
}