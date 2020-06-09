#include "God/Rich.h"
#include "God/God.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"

Rich::Rich()
	:God("Angel")
{

}

bool Rich::init()
{
	initGodImage();
	return true;
}

bool Rich::onLand(Character* standing)
{
	if (setPossesed(standing, rich))
	{
		return true;
	}
	else
	{
		return false;
	}
}