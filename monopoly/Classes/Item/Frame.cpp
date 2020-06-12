#include "Frame.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Incident/Criminal.h"
#include "Incident/PopUpLayer.h"
#include "Scene/GameController.h"
void Frame::work(Character* player) {

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
			SendToJail(character);
			pop->removeFromParentAndCleanup(true);
		});
	}
	pop->setOnScene(51);

}

bool Frame::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "陷害卡";
	content_ = "让一位角色入狱";
	return true;
}