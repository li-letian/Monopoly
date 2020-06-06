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
		if (character->getInsurance() > 0)
		{
			auto pop = PopUpLayer::create();
			pop->setTitle("������Ч");
			pop->setContent(StringUtils::format("���õ�%d�Ĳ���", insurance_value * 2));
			pop->setCallBack([=](Ref* ref) {
				character->setMoney(character->getMoney() + insurance_value * 2);
				character->setVisible(false);
				character->setCurPos(78);
				character->setStopTimes(default_stop_times);
				character->setCondition(in_hospital);
			});
			pop->setPosition(Vec2::ZERO);
			Director::getInstance()->getRunningScene()->addChild(pop, 52);
		}
		else
		{
			character->setVisible(false);
			character->setCurPos(78);
			character->setStopTimes(default_stop_times);
			character->setCondition(in_hospital);
		}
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
			+ std::string("�����Ժ����") + StringUtils::format("%d", stop_times) + std::string("��");
	}
	else
	{
		text = StringUtils::format("%s", character->getPlayerName().c_str())
			+ std::string("�ѳ�Ժ");
		character->setCondition(normal);
		character->setVisible(true);
	}
	pop->setTitle("��Ժ��Ϣ");
	pop->setContent(text);
	pop->setCallBack([=](Ref* sender) {
		SendMsg(msg_make_go_apper);
		});
	pop->setPosition(Vec2(0, 0));
	map_scene->addChild(pop, 50);
}