#include "ControlDice.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Incident/PopUpLayer.h"
#include "Common/CommonConstant.h"

void ControlDice::work(Character* player) {

	auto pop = PopUpLayer::create();
	std::vector<std::string>name;
	std::vector<std::function<void(Ref* ref)>>fun;
	for (int i = 1; i <= walk_steps; i++)
	{
		name.push_back(StringUtils::format("%d", i));
		fun.push_back([=](Ref* ref)
		{
			SetControlDice(player, i);
			pop->removeFromParentAndCleanup(true);
		});
	}
	pop->setMenu(fun, name);
	pop->setOnScene();
}

bool ControlDice::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "遥控骰子";
	content_ = "决定移动步数";
	return true;
}