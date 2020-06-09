#include "God/Angel.h"
#include "God/God.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"

Angel::Angel()
	:God("Angel")
{

}

bool Angel::init()
{
	initGodImage();
	return true;
}

bool Angel::onLand(Character* standing)
{
	if (setPossesed(standing, angel))
	{
		return true;
	}
	else
	{
		return false;
	}
}