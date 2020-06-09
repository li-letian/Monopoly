#include "Luck.h"
#include "God/God.h"
#include "Character/Character.h"
#include "Common/CommonConstant.h"

Luck::Luck()
	:God("Luck")
{

}

bool Luck::init()
{
	initGodImage();
	return true;
}

bool Luck::onLand(Character* standing)
{
	if (setPossesed(standing, luck))
	{
		return true;
	}
	else
	{
		return false;
	}
}