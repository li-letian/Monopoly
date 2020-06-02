#include "Incident/Medical.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Common/CommonMethod.h"

bool SendToHospital(Character* character)
{
	if (character->getStopTimes() > 0)
	{
		return false;
	}
	else
	{
		character->setStopTimes(default_stop_times);
		character->setCondition(in_hospital);
		return true;
	}
}

void PopUpHospitalDialog(Character* character, MapScene* map_scene)
{
	int stop_times = character->getStopTimes();
	auto pop = PopUpLayer::create();
	std::string text;
	if (stop_times > 0)
	{
		text = StringUtils::format("%s", character->getPlayerName().c_str())
			+ std::string("距离出院还有") + StringUtils::format("%d", stop_times) + std::string("天");
	}
	else
	{
		text = StringUtils::format("%s", character->getPlayerName().c_str())
			+ std::string("已出院");
		character->setCondition(normal);
	}
	pop->setTitle("出院消息");
	pop->setContent(text);
	pop->setCallBack([=](Ref* sender) {
		sendMsg(msg_make_go_apper);
		});
	pop->setPosition(Vec2(0, 0));
	map_scene->addChild(pop, 50);
}