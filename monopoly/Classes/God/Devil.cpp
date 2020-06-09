#include "God/Devil.h"
#include "God/God.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"

Devil::Devil()
	:God("Devil")
{

}

bool Devil::init()
{
	initGodImage();
	return true;
}

bool Devil::onLand(Character* standing)
{
	if (setPossesed(standing, devil))
	{
		return true;
	}
	else
	{
		return false;
	}
}