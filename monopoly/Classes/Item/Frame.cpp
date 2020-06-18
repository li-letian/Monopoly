#include "Frame.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Incident/Criminal.h"
#include "Incident/PopUpLayer.h"
#include "Scene/GameController.h"
#include "Scene/ItemScene.h"
void Frame::work(Character* player) {

	auto game_controller = GetGameController();
	auto pop = PopUpLayer::create();
	pop->setTitle("ÇëÑ¡Ôñ");
	std::vector<std::string>pic;
	std::vector<std::function<void(Ref*)>>fun;
	for (auto character : game_controller->getCharacters())
	{
		if (character->getTag() == player->getTag()) continue;
		pic.push_back(character->getPlayerName() + std::string("_avatar.png"));
		fun.push_back([=](Ref* ref)
		{
			SendToJail(character);
			auto item = GetItemScene()->getItem(character, "¸´³ğ¿¨");
			if (item != nullptr)
			{
				item->worked(character);
				SendToJail(player);
				GetItemScene()->removeItem(character, item);
			}
		});
	}
	pop->setMenu(pic,fun);
	pop->setOnScene(51);

}

bool Frame::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "Ïİº¦¿¨";
	content_ = "ÈÃÒ»Î»½ÇÉ«ÈëÓü";
	return true;
}