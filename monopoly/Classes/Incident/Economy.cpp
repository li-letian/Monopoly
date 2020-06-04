#include "Incident/Economy.h"
#include "Common/CommonConstant.h"
#include "Scene/StorkScene.h"

int LevyIncomeTax(Character* character)
{
	int tax = character->getGainValue() / tax_rate;
	character->setGainValue(0);
	return tax;
}

int LevyEstateTax(Character* character)
{
	int tax = character->getEstateValue() / tax_rate;
	return tax;
}

int LevyStockTax(Character* character, StockScene* stock_scene)
{
	int own_sum = 0, tax = 0;
	int tag = character->getTag();
	for (int i = 0; i < stock_scene->stock_vec_.size(); i++)
	{
		int own_num = stock_scene->stock_vec_.at(i)->store_number_.at(tag);
		int price = stock_scene->stock_vec_.at(i)->now_price_;
		own_sum += own_num * price;
	}
	tax = own_sum / tax_rate;
	return tax;
}

Character* GetMostEstate(const Vector<Character*>& characters)
{
	Character* character_most = nullptr;
	int most_value = -1;
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters.at(i)->getEstateValue() > most_value)
		{
			most_value = characters.at(i)->getEstateValue();
			character_most = characters.at(i);
		}
	}
	return character_most;
}

Character* GetLeastEstate(const Vector<Character*>& characters)
{
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
	return character_least;
}

Character* GetMostStock(const Vector<Character*>& characters, StockScene* stock_scene)
{
	Character* character_most = nullptr;
	int most_value = -1;
	for (int i = 0; i < characters.size(); i++)
	{
		auto character = characters.at(i);
		int own_sum = -2;
		int tag = character->getTag();
		for (int j = 0; i < stock_scene->stock_vec_.size(); i++)
		{
			int own_num = stock_scene->stock_vec_.at(i)->store_number_.at(tag);
			int price = stock_scene->stock_vec_.at(i)->now_price_;
			own_sum += own_num * price;
		}
		if (own_sum > most_value)
		{
			most_value = own_sum;
			character_most = character;
		}
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
	character->setMoney(character->getMoney() + help_stock_money);
}