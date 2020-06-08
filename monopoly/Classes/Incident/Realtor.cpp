#include "Incident/Realtor.h"
#include "Common/CommonConstant.h"
#include "Land/Hotel.h"
#include "Character/Dice.h"
#include "Character/Character.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "Land/Land.h"

int GetRandomHotel()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	auto map_scene = GetMapScene();
	auto total = map_scene->totalPosition();
	auto ans = rand() % total;
	while (map_scene->getType(ans) != land_hotel)
		ans = rand() % total;
	auto& land = map_scene->getLand(ans);
	if (!land) land = Hotel::create(static_cast<int>(ans));
	return ans;
}

void SetSellPrice(float rise_rate,int pos)
{
	auto map_scene = GetMapScene();
	auto game_controller = GetGameController();
	auto characters = game_controller->getCharacters();

	if (map_scene->getType(pos) != land_hotel) return;

	for (int index = pos + 1; map_scene->getType(index) == land_hotel || map_scene->getType(index) == land_business; index++)
	{
		if (map_scene->getType(index) == land_business) continue;
		auto& land = map_scene->getLand(index);
		if (!land) land=::Hotel::create(index);
		auto hotel = static_cast<Hotel*>(land);
		hotel->setSellRise(rise_rate);
	}
	for (int index = pos - 1; map_scene->getType(index) == land_hotel || map_scene->getType(index) == land_business; index--)
	{
		if (map_scene->getType(index) == land_business) continue;
		auto& land = map_scene->getLand(index);
		if (!land) land = ::Hotel::create(index);
		auto hotel = static_cast<Hotel*>(land);
		hotel->setSellRise(rise_rate);
	}

	for (int i = 0; i < characters.size(); i++)
	{
		characters.at(i)->setEstateValue(static_cast<int>(characters.at(i)->getEstateValue() * (1 + land_price_rate)));
	}
}

void SellPriceRise(int pos)
{
	SetSellPrice(land_price_rate,pos);
}

void SellPriceDown(int pos)
{
	SetSellPrice(-land_price_rate,pos);
}

void SetRentPrice(float rise_rate,int pos)
{
	auto map_scene = GetMapScene();
	auto game_controller = GetGameController();
	auto characters = game_controller->getCharacters();

	if (map_scene->getType(pos) != land_hotel) return;

	for (int index = pos + 1; map_scene->getType(index) == land_hotel || map_scene->getType(index) == land_business; index++)
	{
		if (map_scene->getType(index) == land_business) continue;
		auto& land = map_scene->getLand(index);
		if (!land) land = ::Hotel::create( index);
		auto hotel = static_cast<Hotel*>(land);
		hotel->setRentRise(rise_rate);
	}
	for (int index = pos - 1; map_scene->getType(index) == land_hotel || map_scene->getType(index) == land_business; index--)
	{
		if (map_scene->getType(index) == land_business) continue;
		auto& land = map_scene->getLand(index);
		if (!land) land = ::Hotel::create(index);
		auto hotel = static_cast<Hotel*>(land);
		hotel->setRentRise(rise_rate);
	}

	for (int i = 0; i < characters.size(); i++)
	{
		characters.at(i)->setEstateValue(static_cast<int>(characters.at(i)->getEstateValue() * (1 + land_price_rate)));
	}
}

void RentPriceUp(int pos)
{
	SetRentPrice(land_price_rate,pos);
}

void RentPriceDown(int pos)
{
	SetRentPrice(-land_price_rate,pos);
}

void FindAllHouses(Vector<Hotel*>& hotels)
{
	auto map_scene = GetMapScene();
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

void FindAllHousesWithOwner(Character* character, Vector<Hotel*>& hotels)
{
	auto map_scene = GetMapScene();
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

void FindAllHotelsWithOwner(Character* character, Vector<Hotel*>& hotels)
{
	auto map_scene = GetMapScene();
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

bool DestroyOneRandomHouse()
{
	auto map_scene = GetMapScene();
	auto pos = GetRandomHotel();
	auto land = map_scene->getLand(pos);
	DestroyHouse(dynamic_cast<Hotel*>(land));
	return true;
}
void DestroyOneStreetHouse(int start_index)
{
	auto map_scene = GetMapScene();
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
}

void PromoteOneStreetHouse(int start_index)
{
	auto map_scene = GetMapScene();
	for (int index = start_index + 1; map_scene->getType(index) == land_hotel || map_scene->getType(index) == land_business; index++)
	{
		if (map_scene->getType(index) == land_business) continue;
		auto land = map_scene->getLand(index);
		if (!land) continue;
		auto hotel = static_cast<Hotel*>(map_scene->getLand(index));
		hotel->promote();
	}
	for (int index = start_index - 1; map_scene->getType(index) == land_hotel || map_scene->getType(index) == land_business; index--)
	{
		if (map_scene->getType(index) == land_business) continue;
		auto land = map_scene->getLand(index);
		if (!land) continue;
		auto hotel = dynamic_cast<Hotel*>(map_scene->getLand(index));
		hotel->promote();
	}
}

bool DestroyOneRandomStreetHouse()
{
	auto map_scene = GetMapScene();
	auto start_index = GetRandomHotel();
	DestroyOneStreetHouse(start_index);
	return true;
}

bool DestroyOneCertainHouse(Character* character)
{
	Vector<Hotel*>hotels;
	FindAllHousesWithOwner(character, hotels);
	if (hotels.empty())
	{
		return false;
	}
	else
	{
		int index = Dice::getARandomNumber(hotels.size());
		DestroyHouse(hotels.at(index));
		return true;
	}
}

bool DestroyOneCertainHotel(Character* character)
{
	Vector<Hotel*>hotels;
	FindAllHousesWithOwner(character, hotels);
	if (hotels.empty())
	{
		return false;
	}
	else
	{
		int index = Dice::getARandomNumber(hotels.size());
		DestroyHouse(hotels.at(index));
		hotels.at(index)->setOwner(nullptr);
		return true;
	}
}