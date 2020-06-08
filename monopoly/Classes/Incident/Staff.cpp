#include "Incident/Staff.h"
#include "Common/CommonConstant.h"
#include "Character/Character.h"

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