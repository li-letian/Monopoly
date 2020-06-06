#include "Character/Dice.h"
#include <ctime>

bool Dice::init()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	return true;
}

int Dice::RollTheDice(int steps_scope)
{
	if (steps_scope == 0)
	{
		return 1;
	}
	else
	{
		return 1 + random(steps_scope);
	}
}

int Dice::getARandomNumber(int scope)
{
	return random(scope);
}