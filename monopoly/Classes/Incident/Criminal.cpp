#include "Incident/Criminal.h"
#include "PopUpLayer.h"
#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"

Criminal::Criminal(MapScene* map_scene, int stop_times)
	:Stay(map_scene, stop_times)
{

}

bool Criminal::eventTrigger(Character* character)
{
	character_ = character;
	if (character_->getStopTimes() > 0)
	{
		return false;
	}
	else
	{
		character_->setStopTimes(stop_times_);
		character_->setCondition(in_jail);
		popUpDialog();
	}
}

void Criminal::popUpDialog()
{
	auto pop = PopUpLayer::create();
	pop->setTitle("入狱");
	auto text = StringUtils::format("%s", character_->getPlayerName().c_str())
		+ std::string("被判罪入狱") + StringUtils::format("%d", stop_times_) + std::string("天");
	pop->setContent(text);
	pop->setCallBack([=](Ref* sender) {
		sendMsg(msg_make_go_apper);
		});
	pop->setPosition(Vec2(0, 0));
	map_scene_->addChild(pop, 50);
}

void Criminal::popUpDialog(Character* character, MapScene* map_scene)
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
	pop->setContent(text);
	pop->setCallBack([=](Ref* sender) {
		sendMsg(msg_make_go_apper);
		});
	pop->setPosition(Vec2(0, 0));
	map_scene->addChild(pop, 50);
}