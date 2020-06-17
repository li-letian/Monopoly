#include "Incident/Staff.h"
#include "Incident/Medical.h"
#include "Incident/PopUpLayer.h"
#include "Incident/Realtor.h"
#include "Incident/Holiday.h"
#include "Common/CommonConstant.h"
#include "Character/Character.h"
#include "Character/Dice.h"
#include "Land/Hotel.h"
#include "Land/Business.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "Scene/StockScene.h"
#include "God/God.h"
#include "God/MinePosition.h"

bool SetSpeedShoes(Character* character)
{
	if (character->getStepsScope() == speed_steps)
	{
		return false;
	}
	else
	{
		character->setStepsScope(speed_steps);
		GetMapScene()->removeChildByName("go_button", true);
		GetGameController()->addGoButton();
		return true;
	}
}

bool SetFlyingShoes(Character* character)
{
	if (character->getStepsScope() == flying_steps)
	{
		return false;
	}
	else
	{
		character->setStepsScope(flying_steps);
		GetMapScene()->removeChildByName("go_button", true);
		GetGameController()->addGoButton();
		return true;
	}
}

bool SetTurtle(Character* character)
{
	if (character->getStepsScope() == turtle_steps)
	{
		return false;
	}
	else
	{
		character->setStepsScope(turtle_steps);
		character->setTurtleTimes(init_turtle_times);
		GetMapScene()->removeChildByName("go_button", true);
		GetGameController()->addGoButton();
		return true;
	}
}

bool DestroySpecialShoes(Character* character)
{
	if (character->getStepsScope() == walk_steps)
	{
		return false;
	}
	else
	{
		character->setStepsScope(walk_steps);
		GetMapScene()->removeChildByName("go_button", true);
		GetGameController()->addGoButton();
		return true;
	}
}

bool SetControlDice(Character* character, int control_point)
{
	if (character->getControlDicePoint() > 0)
	{
		return false;
	}
	else
	{
		character->setControlDicePoint(control_point);
		return true;
	}
}

void UseRobot(Character* user)
{
	auto cur_pos = user->getCurPos();
	auto map_scene = GetMapScene();
	int toward_dir = user->getTowardDirection();
	for (int i = cur_pos; i < cur_pos + 10 * toward_dir; i += toward_dir)
	{
		if (map_scene->getGod(i) != nullptr)
		{
			switch (toward_dir)
			{
			case forward_dir:
				while (1)
				{
					auto index = start_position + Dice::getARandomNumber(total_position - start_position);
					if ((index < cur_pos && index + total_position - 10>cur_pos)
						|| index > cur_pos + 10)
					{
						if (map_scene->getGod(i)->setPos(index, map_scene))
						{
							break;
						}
					}
				}
				break;
			case backward_dir:
				while (1)
				{
					auto index = start_position + Dice::getARandomNumber(total_position - start_position);
					if ((index > cur_pos&& index - total_position + 10 < cur_pos)
						|| index < cur_pos - 10)
					{
						if (map_scene->getGod(i)->setPos(index, map_scene))
						{
							break;
						}
					}
				}
			}
		}
	}
}

void LaunchMissile(Character* user, int target_point)
{
	auto map_scene = GetMapScene();
	auto game_controller = GetGameController();
	auto characters = game_controller->getCharacters();
	Vector<Character*>characters_to_hospital;
	int demote_cnt = 0;
	for (int i = target_point - 1; i <= target_point + 1; i++)
	{
		if (i < 0)
		{
			i = GetMapScene()->totalPosition() - 1;
		}
		for (auto character : characters)
		{
			if (character->getCurPos() == i % map_scene->totalPosition())
			{
				if (character->getStopTimes() == 0)
				{
					characters_to_hospital.pushBack(character);
				}
			}
		}
		if (map_scene->getType(i) == land_hotel && map_scene->getLand(i))
		{
			auto hotel = dynamic_cast<Hotel*>(map_scene->getLand(i));
			auto owner = hotel->getOwner();
			auto pre_value = hotel->getValue();
			if (hotel->demote())
			{
				demote_cnt++;
				owner->setEstateValue(owner->getEstateValue() + hotel->getValue() - pre_value);
			}
		}
	}
	auto pop = PopUpLayer::create();
	pop->setTitle("导弹着陆");
	std::string text = "以下人被炸伤住院:\n";
	for (auto character : characters_to_hospital)
	{
		text = text + character->getPlayerName() + '\n';
	}
	if (demote_cnt > 0)
	{
		text = text + StringUtils::format("有%d栋房屋被严重损坏", demote_cnt);
	}
	pop->setContent(text);
	pop->setCallBack([=](Ref* render) {
		SendToHospital(user,characters_to_hospital);
		});
	pop->setOnScene();
}

bool UseRobotWorker(Character* user, int target_point)
{
	auto map_scene = GetMapScene();
	auto land = map_scene->getLand(target_point);
	if (map_scene->getType(target_point) == land_hotel && land)
	{
		auto hotel = dynamic_cast<Hotel*>(land);
		auto owner = hotel->getOwner();
		auto pre_value = hotel->getValue();
		if (owner == nullptr) return false;
		else if (user == owner)
		{
			hotel->promote();
			user->setEstateValue(user->getEstateValue() + hotel->getValue() - pre_value);
			return true;
		}
		else
		{
			if (hotel->demote())
			{
				owner->setEstateValue(owner->getEstateValue() + hotel->getValue() - pre_value);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
}

bool UseDevilCard(int target_point)
{
	auto map_scene = GetMapScene();
	if (map_scene->getType(target_point) == land_hotel && map_scene->getLand(target_point))
	{
		DestroyOneStreetHouse(target_point);
		return true;
	}
	else
	{
		return false;
	}
}


bool UseAngelCard(int target_point)
{
	auto map_scene = GetMapScene();
	if (map_scene->getType(target_point) == land_hotel && map_scene->getLand(target_point))
	{
		PromoteOneStreetHouse(target_point);
		return true;
	}
	else
	{
		return false;
	}
}

bool TransmitGod(God*target,int target_point)
{
	if (target->setPos(target_point,GetMapScene()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TransmitCharacter(Character* user, Character* target, int target_point)
{
	auto map_scene = GetMapScene();
	auto game_controller = GetGameController();
	if (target->getCondition() == normal)
	{
		if (user == target)
		{
			SendMsg(msg_hide_go_only);
			user->setPosition(map_scene->pos(target_point));
			user->setCurPos(target_point);
			game_controller->backToStand(user);
			auto endGoCallFunc = CallFunc::create([=]() {
				game_controller->endGo();
				});
			auto sequnce = Sequence::create(DelayTime::create(0.5f), endGoCallFunc, nullptr);
			map_scene->runAction(sequnce);
		}
		else
		{
			target->setPosition(map_scene->pos(target_point));
			target->setCurPos(target_point);
			game_controller->backToStand(target);
			auto returnToCharacterCallFunc = CallFunc::create([=]() {
				game_controller->returnToCharacter(user);
				});
			auto sequnce = Sequence::create(DelayTime::create(0.5f), returnToCharacterCallFunc, nullptr);
			map_scene->runAction(sequnce);
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool UseHouseDestroy(int target_point)
{
	auto map_scene = GetMapScene();
	auto land = map_scene->getLand(target_point);
	if (map_scene->getType(target_point) == land_hotel && land)
	{
		auto hotel = dynamic_cast<Hotel*>(land);
		if (hotel->getRank() > 0)
		{
			DestroyHouse(hotel);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool UseHouseExchange(int house1_pos, int house2_pos)
{
	auto map_scene = GetMapScene();
	auto land1 = map_scene->getLand(house1_pos);
	auto land2 = map_scene->getLand(house2_pos);
	if (land1 && land2 && map_scene->getType(house1_pos) == land_hotel && map_scene->getType(house2_pos))
	{
		auto hotel1 = dynamic_cast<Hotel*>(land1);
		auto hotel2 = dynamic_cast<Hotel*>(land2);
		int rank1 = hotel1->getRank();
		int rank2 = hotel2->getRank();
		auto high_rank_hotel = rank1 > rank2 ? hotel1 : hotel2;
		auto low_rank_hotel = rank1 < rank2 ? hotel1 : hotel2;
		auto high_pre_value = high_rank_hotel->getValue();
		auto low_pre_value = low_rank_hotel->getValue();
		for (int i = 0; i < abs(rank1 - rank2); i++)
		{
			high_rank_hotel->demote();
			low_rank_hotel->promote();
		}
		auto owner_high = high_rank_hotel->getOwner();
		auto owner_low = low_rank_hotel->getOwner();
		owner_high->setEstateValue(owner_high->getEstateValue() + high_rank_hotel->getValue() - high_pre_value);
		owner_low->setEstateValue(owner_low->getEstateValue() + low_rank_hotel->getValue() - low_pre_value);
		return true;
	}
	else
	{
		return false;
	}
}

bool UseHouseBuy(Character* user, int target_point)
{
	return true;
}

bool UseHouseBuy(Character* user)
{
	auto target_point = user->getCurPos();
	auto map_scene = GetMapScene();
	auto land = map_scene->getLand(target_point);
	if (land && map_scene->getType(target_point) == land_hotel)
	{
		auto hotel = dynamic_cast<Hotel*>(land);
		auto owner = hotel->getOwner();
		if (owner != user)
		{
			if (user->getMoney() >= hotel->getValue())
			{
				user->setMoney(user->getMoney() - hotel->getValue());
				owner->setEstateValue(owner->getEstateValue() - hotel->getValue());
				user->setEstateValue(user->getEstateValue() + hotel->getValue());
				hotel->setOwner(user);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool UseHouseChange(int target_point)
{
	auto map_scene = GetMapScene();
	auto land = map_scene->getLand(target_point);
	if (land && map_scene->getType(target_point) == land_business)
	{
		auto business = dynamic_cast<Business*>(land);
		business->demote();
		business->promote(true);
		return true;
	}
	else
	{
		return false;
	}
}

bool UseRisePriceCard(int target_point)
{
	auto map_scene = GetMapScene();
	auto land = map_scene->getLand(target_point);
	if (land && map_scene->getType(target_point) == land_hotel)
	{
		SetSellPrice(land_price_rate, target_point);
		return true;
	}
	else
	{
		return false;
	}
}

void setUserStocks(Character* user, int up_or_down)
{
	auto stock_scene = GetStockScene();
	auto stocks = stock_scene->getStock();
	int tag = user->getTag();
	for (auto stock : stocks)
	{
		if (stock->store_number_[tag] > 0)
		{
			stock->setCondition(up_or_down);
			stock->setDurationTime(market_duration_time);
		}
	}
}

void UseRedCard(Character* user)
{
	setUserStocks(user, up_market);
}

void UseBlackCard(Character* user)
{
	auto characters = GetGameController()->getCharacters();
	for (auto character : characters)
	{
		if (character != user)
		{
			setUserStocks(character, down_market);
		}
	}
}

bool UseAverageCard(Character* user, Character* target)
{
	if (user == target)
	{

		return false;
	}
	else
	{
		int average_money = (user->getMoney() + target->getMoney()) / 2;
		user->setMoney(average_money);
		target->setMoney(average_money);
		return true;
	}
}

bool UseStayCard(Character* target)
{
	if (target->getCondition() == normal)
	{
		target->setIsStay(true);
		return true;
	}
	else
	{
		return false;
	}
}

bool UseTurnAroundCard(Character* user)
{
	if (user->getCondition() != normal)
	{
		return false;
	}
	else
	{
		if (user->getTowardDirection() == forward_dir)
		{
			user->setTowardDirection(backward_dir);
		}
		else
		{
			user->setTowardDirection(forward_dir);
		}
		auto game_controller = GetGameController();
		game_controller->backToStand(user);
		return true;
	}
}

void UseHolidayCard(Character* user)
{
	auto characters = GetGameController()->getCharacters();
	for (auto character : characters)
	{
		if (character != user && character->getCondition() == normal)
		{
			GoOnHoliday(character);
		}
	}
}

bool UsePrayCard(Character* user)
{
	if (user->getGodPossessed() != no_god)
	{
		return false;
	}
	auto gods = GetGameController()->getGods();
	int min_distance = GetMapScene()->totalPosition();
	God* prayed_god = nullptr;
	for (auto god : gods)
	{
		int bigger_pos = max(god->getPos(), user->getCurPos());
		int smaller_pos = min(god->getPos(), user->getCurPos());
		int cur_distance = min(bigger_pos - smaller_pos, smaller_pos - bigger_pos + GetMapScene()->totalPosition() - 1);
		if (cur_distance < min_distance)
		{
			min_distance = cur_distance;
			prayed_god = god;
		}
	}
	if (prayed_god == nullptr)
	{
		return false;
	}
	prayed_god->removeGodFromMap();
	prayed_god->addToCharacter(user);
	prayed_god->popUpExplain(false);
	return true;
}

bool SetMinePosition(int target_point)
{
	auto mine_pos = MinePosition::create();
	if (mine_pos->setPos(target_point, GetMapScene()))
	{
		GetMapScene()->getMap()->addChild(mine_pos, 10);
		return true;
	}
	else
	{
		return false;
	}
}