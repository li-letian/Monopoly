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
		for (auto character : characters)
		{
			if (character->getCurPos() == i)
			{
				SendToHospital(character);
				characters_to_hospital.pushBack(character);
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
	for (auto character : characters_to_hospital)
	{
		text = text + character->getPlayerName() + '\n';
	}
	text = text + StringUtils::format("有%d栋房屋被严重损坏", demote_cnt);
	pop->setCallBack([=](Ref* render) {

		});
	pop->setOnScene();
}

bool UseRobotWorker(Character* user, int target_point)
{
	auto map_scene = GetMapScene();
	auto game_controller = GetGameController();
	auto characters = game_controller->getCharacters();
	auto land = map_scene->getLand(target_point);
	if (map_scene->getType(target_point) == land_hotel && land)
	{
		auto hotel = dynamic_cast<Hotel*>(land);
		for (auto character:characters)
		{
			if (character == hotel->getOwner())
			{
				if (character == user)
				{
					hotel->promote();
					return true;
				}
				else
				{
					if (hotel->demote())
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
	else
	{
		return false;
	}
}