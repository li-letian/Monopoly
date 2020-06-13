#include "Escape.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Incident/PopUpLayer.h"

void Escape::worked(Character* player) 
{
	auto pop = PopUpLayer::create();
	pop->setTitle(name_);
	pop->setContent("�ɹ�����");
	auto seq = Sequence::create(DelayTime::create(0.3f), CallFunc::create([=]() {pop->removeFromParentAndCleanup(true); }), nullptr);
	pop->runAction(seq);
	pop->setOnScene();
}

bool Escape::init()
{
	if (!Item::init())
	{
		return false;
	}
	name_ = "��ң����";
	content_ = "��������һ�����´���";
	return true;
}