#include "Incident/Economy.h"
#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"
#include "Scene/StockScene.h"
#include "Scene/GameController.h"
#include "Character/Character.h"
#include "Character/Dice.h"
int LevyIncomeTax(Character* character)
{
	auto tax =static_cast<int>(character->getGainValue() / tax_rate);
	character->setGainValue(0);
	return tax;
}

int LevyEstateTax(Character* character)
{
	auto tax = static_cast<int>(character->getEstateValue() / tax_rate);
	return tax;
}

int LevyStockTax(Character* character)
{
	auto stock_scene = GetStockScene();
	auto own_sum = 0, tax = 0;
	auto tag = character->getTag();
	for (int i = 0; i < stock_scene->getStock().size(); i++)
	{
		int own_num = stock_scene->getStock().at(i)->store_number_.at(tag);
		int price = stock_scene->getStock().at(i)->now_price_;
		own_sum += own_num * price;
	}
	tax = static_cast<int>(own_sum / tax_rate);
	return tax;
}

Character* GetMostEstate()
{
	auto game_controller = GetGameController();
	auto characters = game_controller->getCharacters();
	Character* character_most = nullptr;
	int most_value = 0;
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters.at(i)->getEstateValue() > most_value)
		{
			most_value = characters.at(i)->getEstateValue();
			character_most = characters.at(i);
		}
	}
	if (character_most == nullptr)
	{
		character_most = characters.at(Dice::getARandomNumber(characters.size()));
	}
	return character_most;
}

Character* GetLeastEstate()
{
	auto game_controller = GetGameController();
	auto characters = game_controller->getCharacters();
	Character* character_least = nullptr;
	int least_value = 2000000000;
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters.at(i)->getEstateValue() < least_value)
		{
			least_value = characters.at(i)->getEstateValue();
			character_least = characters.at(i);
		}
	}
	if (least_value == 0 && characters.at(0) == character_least)
	{
		character_least = characters.at(Dice::getARandomNumber(characters.size()));
	}
	return character_least;
}

Character* GetMostStock()
{
	auto game_controller = GetGameController();
	auto characters = game_controller->getCharacters();
	auto stock_scene = GetStockScene();
	Character* character_most = nullptr;
	int most_value = 0;
	for (int i = 0; i < characters.size(); i++)
	{
		auto character = characters.at(i);
		int own_sum = 0;
		int tag = character->getTag();
		for (int j = 0; i < stock_scene->getStock().size(); i++)
		{
			int own_num = stock_scene->getStock().at(i)->store_number_.at(tag);
			int price = stock_scene->getStock().at(i)->now_price_;
			own_sum += own_num * price;
		}
		if (own_sum > most_value)
		{
			most_value = own_sum;
			character_most = character;
		}
	}
	if (character_most == nullptr)
	{
		character_most = characters.at(Dice::getARandomNumber(characters.size()));
	}
	return character_most;
}

void RewardMostEstate(Character* character)
{
	character->setMoney(character->getMoney() + reward_estate_money);
}

void HelpLeastEstate(Character* character)
{
	character->setMoney(character->getMoney() + help_estate_money);
}

void RewardMostStock(Character* character)
{
	character->setMoney(character->getMoney() + reward_stock_money);
}

void TraficFine(Character* character)
{
	character->setMoney(character->getMoney() - traffic_fine);
}