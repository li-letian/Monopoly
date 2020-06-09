#include "God/Unluck.h"
#include "God/God.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"

Unluck::Unluck()
	:God("Unluck")
{

}

bool Unluck::init()
{
	initGodImage();
	return true;
}

bool Unluck::onLand(Character* standing)
{
	if (setPossesed(standing, unluck))
	{
		return true;
	}
	else
	{
		return false;
	}
}