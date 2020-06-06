#include "Incident/Staff.h"
#include "Common/CommonConstant.h"

bool SetMotor(Character* character)
{
	if (character->getStepsScope() == motor_steps)
	{
		return false;
	}
	else
	{
		character->setStepsScope(motor_steps);
		return true;
	}
}

bool SetCar(Character* character)
{
	if (character->getStepsScope() == car_steps)
	{
		return false;
	}
	else
	{
		character->setStepsScope(car_steps);
		return true;
	}
}

bool DestroyTrafficTool(Character* character)
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