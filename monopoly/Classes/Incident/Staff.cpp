#include "Incident/Staff.h"
#include "Incident/Medical.h"
#include "Incident/PopUpLayer.h"
#include "Common/CommonConstant.h"
#include "Character/Character.h"
#include "Land/Hotel.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"

bool SetSpeedShoes(Character* character)
{
	if (character->getStepsScope() == speed_steps)
	{
		return false;
	}
	else
	{
		character->setStepsScope(speed_steps);
		return true;
	}
}

bool SetFlyingShoes(Character* character)
{
	if (character->getStepsScope() == flying_steps)
	{
		return false;
	}
	else
	{
		character->setStepsScope(flying_steps);
		return true;
	}
}

bool SetTurtle(Character* character)
{
	if (character->getStepsScope() == turtle_steps)
	{
		return false;
	}
	else
	{
		character->setStepsScope(turtle_steps);
		character->setTurtleTimes(init_turtle_times);
		return true;
	}
}

bool DestroySpecialShoes(Character* character)
{
	if (character->getStepsScope() == walk_steps)
	{
		return false;
	}
	else
	{
		character->setStepsScope(walk_steps);
		return true;
	}
}

bool SetControlDice(Character* character, int control_point)
{
	if (character->getControlDicePoint() > 0)
	{
		return false;
	}
	else
	{
		character->setControlDicePoint(control_point);
		return true;
	}
}

void LaunchMissile(int target_point)
{
	auto map_scene = GetMapScene();
	auto game_controller = GetGameController();
	auto characters = game_controller->getCharacters();
	Vector<Character*>characters_to_hospital;
	int demote_cnt = 0;
	for (int i = target_point - 1; i <= target_point + 1; i++)
	{
		for (int j = 0; j < characters.size(); j++)
		{
			if (characters.at(i)->getCurPos() == i)
			{
				SendToHospital(characters.at(i));
				characters_to_hospital.pushBack(characters.at(i));
			}
		}
		if (map_scene->getType(i) == land_hotel && map_scene->getLand(i))
		{
			auto hotel = dynamic_cast<Hotel*>(map_scene->getLand(i));
			if (hotel->demote())
			{
				demote_cnt++;
			}
		}
	}
	auto pop = PopUpLayer::create();
	pop->setTitle("导弹着陆");
	std::string text = "以下人被炸伤住院:\n";
	for (int i = 0; i < characters_to_hospital.size(); i++)
	{
		text = text + characters_to_hospital.at(i)->getPlayerName() + '\n';
	}
	text = text + StringUtils::format("有%d栋房屋被严重损坏", demote_cnt);
	pop->setCallBack([=](Ref* render) {

		});
	pop->setOnScene();
}