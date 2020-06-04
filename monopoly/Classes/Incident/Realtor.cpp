#include "Incident/Realtor.h"
#include "Common/CommonConstant.h"
#include "Land/Hotel.h"

void SetSellPrice(Vector<Character*>characters, MapScene* map_scene, float rise_rate)
{
	for (int i = 0; i < map_scene->totalPosition(); i++)
	{
		if (map_scene->getType(i) == land_hotel)
		{
			auto hotel = dynamic_cast<Hotel*>(map_scene->getLand(i));
			hotel->setSellRise(rise_rate);
		}
	}
	for (int i = 0; i < characters.size(); i++)
	{
		characters.at(i)->setEstateValue(static_cast<int>(characters.at(i)->getEstateValue() * (1 + land_price_rate)));
	}
}

void SellPriceRise(Vector<Character*>characters, MapScene* map_scene)
{
	SetSellPrice(characters, map_scene, land_price_rate);
}

void SellPriceDown(Vector<Character*>characters, MapScene* map_scene)
{
	SetSellPrice(characters, map_scene, -land_price_rate);
}

void SetRentPrice(Vector<Character*>characters, MapScene* map_scene, float rise_rate)
{
	for (int i = 0; i < map_scene->totalPosition(); i++)
	{
		if (map_scene->getType(i) == land_hotel)
		{
			auto hotel = dynamic_cast<Hotel*>(map_scene->getLand(i));
			hotel->setRentRise(rise_rate);
		}
	}
	for (int i = 0; i < characters.size(); i++)
	{
		characters.at(i)->setEstateValue(static_cast<int>(characters.at(i)->getEstateValue() * (1 + land_price_rate)));
	}
}

void RentPriceUp(Vector<Character*>characters, MapScene* map_scene)
{
	SetRentPrice(characters, map_scene, land_price_rate);
}

void RentPriceDown(Vector<Character*>characters, MapScene* map_scene)
{
	SetRentPrice(characters, map_scene, -land_price_rate);
}