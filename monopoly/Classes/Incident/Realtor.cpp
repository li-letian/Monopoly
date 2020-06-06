#include "Incident/Realtor.h"
#include "Common/CommonConstant.h"
#include "Land/Hotel.h"
#include "Character/Dice.h"

void SetSellPrice(Vector<Character*>& characters, MapScene* map_scene, float rise_rate)
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

void SellPriceRise(Vector<Character*>& characters, MapScene* map_scene)
{
	SetSellPrice(characters, map_scene, land_price_rate);
}

void SellPriceDown(Vector<Character*>& characters, MapScene* map_scene)
{
	SetSellPrice(characters, map_scene, -land_price_rate);
}

void SetRentPrice(Vector<Character*>& characters, MapScene* map_scene, float rise_rate)
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

void RentPriceUp(Vector<Character*>& characters, MapScene* map_scene)
{
	SetRentPrice(characters, map_scene, land_price_rate);
}

void RentPriceDown(Vector<Character*>& characters, MapScene* map_scene)
{
	SetRentPrice(characters, map_scene, -land_price_rate);
}

void FindAllHouses(MapScene* map_scene, Vector<Hotel*>& hotels)
{
	for (int i = 0; i < map_scene->totalPosition(); i++)
	{
		auto land = map_scene->getLand(i);
		if (land && map_scene->getType(i) == land_hotel)
		{
			auto hotel = dynamic_cast<Hotel*>(map_scene->getLand(i));
			if (hotel->getRank() >= 1)
			{
				hotels.pushBack(hotel);
			}
		}
	}
}

void FindAllHousesWithOwner(Character* character, MapScene* map_scene, Vector<Hotel*>& hotels)
{
	for (int i = 0; i < map_scene->totalPosition(); i++)
	{
		auto land = map_scene->getLand(i);
		if (land && map_scene->getType(i) == land_hotel)
		{
			auto hotel = dynamic_cast<Hotel*>(map_scene->getLand(i));
			if (hotel->getOwner() == character && hotel->getRank() >= 1)
			{
				hotels.pushBack(hotel);
			}
		}
	}
}

void FindAllHotelsWithOwner(Character* character, MapScene* map_scene, Vector<Hotel*>& hotels)
{
	for (int i = 0; i < map_scene->totalPosition(); i++)
	{
		auto land = map_scene->getLand(i);
		if (land && map_scene->getType(i) == land_hotel)
		{
			auto hotel = dynamic_cast<Hotel*>(map_scene->getLand(i));
			if (hotel->getOwner() == character)
			{
				hotels.pushBack(hotel);
			}
		}
	}
}

void DestroyHouse(Hotel* hotel)
{
	while (hotel->demote())
	{
		;
	}
}

bool DestroyOneRandomHouse(MapScene*map_scene)
{
	Vector<Hotel*>hotels;
	FindAllHouses(map_scene, hotels);
	if (hotels.empty())
	{
		return false;
	}
	else
	{
		int index = Dice::getARandomNumber(hotels.size() - 1);
		DestroyHouse(hotels.at(index));
		return true;
	}
}

bool DestroyOneRandomStreetHouse(MapScene* map_scene)
{
	Vector<Hotel*>hotels;
	FindAllHouses(map_scene, hotels);
	if (hotels.empty())
	{
		return false;
	}
	else
	{
		auto hotel_start = hotels.at(Dice::getARandomNumber(hotels.size() - 1));
		int start_index = 0;
		for (int i = 0; i < map_scene->totalPosition(); i++)
		{
			if (hotel_start == map_scene->getLand(i))
			{
				start_index = i;
				break;
			}
		}
		for (int index = start_index + 1; map_scene->getType(index) == land_hotel || map_scene->getType(index) == land_business; index++)
		{
			if (map_scene->getType(index) == land_business) continue;
			auto land = map_scene->getLand(index);
			if (!land) continue;
			auto hotel = static_cast<Hotel*>(map_scene->getLand(index));
			DestroyHouse(hotel);
		}
		for (int index = start_index - 1; map_scene->getType(index) == land_hotel || map_scene->getType(index) == land_business; index--)
		{
			if (map_scene->getType(index) == land_business) continue;
			auto land = map_scene->getLand(index);
			if (!land) continue;
			auto hotel = dynamic_cast<Hotel*>(map_scene->getLand(index));
			DestroyHouse(hotel);
		}
		return true;
	}
}

bool DestroyOneCertainHouse(Character* character, MapScene* map_scene)
{
	Vector<Hotel*>hotels;
	FindAllHousesWithOwner(character, map_scene, hotels);
	if (hotels.empty())
	{
		return false;
	}
	else
	{
		int index = Dice::getARandomNumber(hotels.size() - 1);
		DestroyHouse(hotels.at(index));
		return true;
	}
}

bool DestroyOneCertainHotel(Character* character, MapScene* map_scene)
{
	Vector<Hotel*>hotels;
	FindAllHousesWithOwner(character, map_scene, hotels);
	if (hotels.empty())
	{
		return false;
	}
	else
	{
		int index = Dice::getARandomNumber(hotels.size() - 1);
		DestroyHouse(hotels.at(index));
		hotels.at(index)->setOwner(nullptr);
		return true;
	}
}