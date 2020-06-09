#include "God/Earth.h"
#include "God/God.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"

Earth::Earth()
	:God("Earth")
{
	
}

bool Earth::init()
{
	initGodImage();
	return true;
}

bool Earth::onLand(Character* standing)
{
	if (setPossesed(standing, earth))
	{
		return true;
	}
	else
	{
		return false;
	}
}

