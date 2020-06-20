#include "Incident/Medical.h"
#include "Common/CommonConstant.h"
#include "Incident/PopUpLayer.h"
#include "Common/CommonMethod.h"
#include "Character/Character.h"

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
			pop->setTitle("保险生效");
			pop->setContent(StringUtils::format("你会得到%d的补偿", insurance_value * 2));
			pop->setCallBack([=](Ref* ref) {
				character->setMoney(character->getMoney() + insurance_value * 2);
				character->setVisible(false);
				character->setCurPos(78);
				character->setPosition(GetMapScene()->pos(78));
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
			character->setPosition(GetMapScene()->pos(78));
			character->setStopTimes(default_stop_times);
			character->setCondition(in_hospital);
		}
		return true;
	}
}

bool SendToHospital(Character*user,Vector<Character*>characters_to_hospital)
{
	Vector<Character*>characters_have_insurance;
	for (auto character : characters_to_hospital)
	{
		if (character->getInsurance() > 0)
		{
			characters_have_insurance.pushBack(character);
		}
		character->setVisible(false);
		character->setCurPos(78);
		character->setPosition(GetMapScene()->pos(78));
		character->setStopTimes(default_stop_times);
		character->setCondition(in_hospital);
	}
	if (characters_have_insurance.size() > 0)
	{
		auto pop = PopUpLayer::create();
		pop->setTitle("保险生效");
		auto text = std::string("以下人得到补偿\n");
		for (auto character : characters_have_insurance)
		{
			text = text + character->getPlayerName() + StringUtils::format(":%d\n", insurance_value * 2);
			character->setMoney(character->getMoney() + insurance_value * 2);
		}
		pop->setContent(text);
		pop->setCallBack([=](Ref* render) {
			for (int i = 0; i < characters_to_hospital.size(); i++)
			{
				if (characters_to_hospital.at(i) == user)
				{
					SendMsg(msg_hide_go_only);
					SendMsg(msg_make_go_appear);
				}
			}
			});
		pop->setOnScene();
	}
	else
	{
		for (int i = 0; i < characters_to_hospital.size(); i++)
		{
			if (characters_to_hospital.at(i) == user)
			{
				SendMsg(msg_hide_go_only);
				SendMsg(msg_make_go_appear);
			}
		}
	}
	
	return true;
}

void PopUpHospitalDialog(Character* character)
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
		character->setCurPos(78);
		character->setPosition(GetMapScene()->pos(78));
		character->setVisible(true);
	}
	pop->setTitle("出院消息");
	pop->setContent(text);
	pop->setCallBack([=](Ref* sender) {
		SendMsg(msg_make_go_appear);
		});
	pop->setOnScene();
}