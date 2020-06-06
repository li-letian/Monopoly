#include "Incident/Criminal.h"
#include "PopUpLayer.h"
#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"

bool SendToJail(Character* character)
{
	if (character->getStopTimes() > 0)
	{
		return false;
	}
	else
	{
		character->setVisible(false);
		character->setCurPos(283);
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
			+ std::string("�����������") + StringUtils::format("%d", stop_times) + std::string("��");
	}
	else
	{
		text = StringUtils::format("%s", character->getPlayerName().c_str())
			+ std::string("�ѳ���");
		character->setCondition(normal);
		character->setVisible(true);
	}
	pop->setTitle("����Ԥ��");
	pop->setContent(text);
	pop->setCallBack([=](Ref* sender) {
		SendMsg(msg_make_go_apper);
		});
	pop->setOnScene();
}