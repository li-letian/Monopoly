#include "GameController.h"

GameController* GameController::game_controller_instance_ = NULL;

bool GameController::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//Î´Íê
	return true;
}

GameController* GameController::getInstance()
{
	if (!game_controller_instance_)
	{
		game_controller_instance_ = GameController::create();
	}
	game_controller_instance_->retain();
	return game_controller_instance_;
}