#include "Average.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Incident/PopUpLayer.h"
#include "Scene/GameController.h"

void Average::work(Character* player) {
	auto game_controller = GetGameController();
	auto pop = PopUpLayer::create();
	pop->setTitle("请选择");
	std::vector<std::string>txt;
	std::vector<std::function<void(Ref*)>>fun;
	for (auto character : game_controller->getCharacters())
	{
		txt.push_back(character->getPlayerName());
		fun.push_back([=](Ref* ref)
		{
			UseAverageCard(player, character);
			pop->removeFromParentAndCleanup(true);
		});
	}
	pop->setOnScene(51);
}

bool Average::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "共同富裕";
	content_ = "指定一人于其平分现金";
	return true;
}