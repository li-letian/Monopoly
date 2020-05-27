#include "Character/Dice.h"
#include <ctime>

bool Dice::init()
{
	srand(static_cast<int>(time(0)));
	return true;
}

int Dice::RollTheDice(int steps_scope)
{
	return 1 + random(steps_scope);
}