#include "Incident/Criminal.h"
#include "PopUpLayer.h"
#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"

bool SendToJail(Character* character)
{
	if (character->getStopTimes() > 0)
	{
		return false;
	}
	else
	{
		character->setStopTimes(default_stop_times);
		character->setCondition(in_jail);
		return true;
	}
}

void PopUpJailDialog(Character* character,MapScene* map_scene)
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
	}
	pop->setTitle("出狱预告");
	pop->setContent(text);
	pop->setCallBack([=](Ref* sender) {
		sendMsg(msg_make_go_apper);
		});
	pop->setPosition(Vec2(0, 0));
	map_scene->addChild(pop, 50);
}