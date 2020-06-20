#include "Revenge.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Incident/PopUpLayer.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"

void Revenge::worked(Character* player)
{
	auto pop = PopUpLayer::create();
	pop->setTitle(name_);
	pop->setContent("�ɹ�����");
	auto seq = Sequence::create(DelayTime::create(0.3f), CallFunc::create([=]() {
		pop->removeFromParentAndCleanup(true);
		SendMsg(msg_hide_go_only);
		SendMsg(msg_make_go_appear);
	}), nullptr);
	pop->runAction(seq);
	pop->setOnScene();
}

bool Revenge::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "����";
	content_ = "������ʵʩ������ͬ�����´������������������ȷ������";
	return true;
}