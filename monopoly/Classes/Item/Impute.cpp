#include "Impute.h"
#include "Character/Character.h"
#include "Incident/Staff.h"
#include "Incident/PopUpLayer.h"

void Impute::worked(Character* player)
{
	auto pop = PopUpLayer::create();
	pop->setTitle(name_);
	pop->setContent("成功脱罪");
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
	name_ = "嫁祸卡";
	content_ = "可以将刑事处罚嫁祸给他人，被动触发，点击确认则作废";
	return true;
}