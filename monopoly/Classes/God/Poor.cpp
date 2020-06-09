#include "God/Poor.h"
#include "God/God.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"

Poor::Poor()
	:God("Poor")
{

}

bool Poor::init()
{
	initGodImage();
	return true;
}

bool Poor::onLand(Character* standing)
{
	if (setPossesed(standing, poor))
	{
		return true;
	}
	else
	{
		return false;
	}
}