#include "Incident/Economy.h"
#include "Common/CommonConstant.h"

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

void RewardMostEstate(Character* character)
{
	character->setMoney(character->getMoney() + reward_estate_money);
}

void HelpLeastEstate(Character* character)
{
	character->setMoney(character->getMoney() + help_estate_money);
}