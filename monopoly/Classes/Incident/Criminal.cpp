#include "Incident/Criminal.h"
#include "PopUpLayer.h"
#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"
#include "Scene/ItemScene.h"
#include "Item/Item.h"
#include "Scene/GameController.h"

bool SendToJail(Character* character)
{
	auto item = GetItemScene()->getItem(character, "逍遥法外");
	if (item!=nullptr)
	{
		item->worked(character);
		GetItemScene()->removeItem(character, item);
		return true;
	}
	item = GetItemScene()->getItem(character, "嫁祸卡");
	if (item != nullptr)
	{
		auto pop = PopUpLayer::create();
		std::vector<std::string>pic;
		std::vector<std::function<void(Ref*)>>fun;
		auto characters = GetGameController()->getCharacters();
		for (auto c : characters)
		{
			if (character->getTag() == c->getTag()) continue;
			pic.push_back(c->getPlayerName() + std::string("_avatar.png"));
			fun.push_back([=](Ref* ref)
			{
				if (c->getStopTimes() > 0)
				{
					return;
				}
				else
				{
					c->setVisible(false);
					c->setCurPos(283);
					c->setPosition(GetMapScene()->pos(238));
					c->setStopTimes(default_stop_times);
					c->setCondition(in_jail);
					return;
				}
				GetItemScene()->removeItem(character, item);
				pop->removeFromParentAndCleanup(true);
			});
		}
		pop->setTitle("请选择嫁祸给");
		pop->setMenu(pic,fun);
		item->worked(character);
		pop->setOnScene();
		return true;
	}
	if (character->getStopTimes() > 0)
	{
		character->setVisible(false);
		character->setCurPos(283);
		return false;
	}
	else
	{
		character->setVisible(false);
		character->setCurPos(283);
		character->setPosition(GetMapScene()->pos(238));
		character->setStopTimes(default_stop_times);
		character->setCondition(in_jail);
		return true;
	}
}

void PopUpJailDialog(Character* character)
{
	int stop_times = character->getStopTimes();
	auto pop = PopUpLayer::create();
	std::string text;
	if (stop_times > 0)
	{
		text = StringUtils::format("%s", character->getPlayerName().c_str())
			+ std::string("距离出狱还有") + StringUtils::format("%d", stop_times) + std::string("天");
	}
	else
	{
		text = StringUtils::format("%s", character->getPlayerName().c_str())
			+ std::string("已出狱");
		character->setCondition(normal);
		character->setCurPos(283);
		character->setPosition(GetMapScene()->pos(238));
		character->setVisible(true);
	}
	pop->setTitle("出狱预告");
	pop->setContent(text);
	pop->setCallBack([=](Ref* sender) {
		SendMsg(msg_make_go_appear);
		});
	pop->setOnScene();
}