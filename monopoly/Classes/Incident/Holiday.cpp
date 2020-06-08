#include "Incident/Holiday.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"

bool GoOnHoliday(Character* character)
{
	if (character->getStopTimes() > 0)
	{
		return false;
	}
	else
	{
		character->setVisible(false);
		character->setStopTimes(default_stop_times);
		character->setCondition(on_holiday);
		return true;
	}
}

void PopUpHolidayDialog(Character* character)
{
	int stop_times = character->getStopTimes();
	auto pop = PopUpLayer::create();
	std::string text;
	if (stop_times > 0)
	{
		text = StringUtils::format("%s", character->getPlayerName().c_str())
			+ std::string("距离度假归来还有") + StringUtils::format("%d", stop_times) + std::string("天");
	}
	else
	{
		text = StringUtils::format("%s", character->getPlayerName().c_str())
			+ std::string("已度假归来");
		character->setCondition(normal);
		character->setVisible(true);
	}
	pop->setTitle("度假消息");
	pop->setContent(text);
	pop->setCallBack([=](Ref* sender) {
		SendMsg(msg_make_go_apper);
		});
	pop->setOnScene();
}