#include "Impute.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Incident/PopUpLayer.h"

void Impute::worked(Character* player)
{
	auto pop = PopUpLayer::create();
	pop->setTitle(name_);
	pop->setContent("�ɹ�����");
	auto seq = Sequence::create(DelayTime::create(0.3f), CallFunc::create([=]() {pop->removeFromParentAndCleanup(true); }), nullptr);
	pop->runAction(seq);
	pop->setOnScene();
}

bool Impute::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "�޻���";
	content_ = "���Խ����´����޻������ˣ��������������ȷ��������";
	return true;
}