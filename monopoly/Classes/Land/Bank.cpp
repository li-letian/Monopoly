#include "Bank.h"
#include "cocos2d.h"
#include "Land.h"
#include "Common/CommonConstant.h"
#include "Scene/GameController.h"
#include "Scene/MapScene.h"
#include "Incident/PopUpLayer.h"
#include<string>
#include "Common/CommonMethod.h"

USING_NS_CC;

Bank* Bank::create(int index)
{
	auto pRet = new(std::nothrow) Bank();
	if (pRet && pRet->init())
	{
		auto map_scene = GetMapScene();
		pRet->index_ = index;
		pRet->name_ = std::string("中央银行");
		pRet->setAnchorPoint(Vec2(0.5f, 0.5f));
		pRet->setPosition(map_scene->pos(index));
		map_scene->getMap()->addChild(pRet, 1);
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool Bank::onLand(Character* standing)
{
	auto pop = PopUpLayer::create();
	auto map_scene = GetMapScene();
	pop->setTitle(name_);
	std::vector<std::string>txt;
	std::vector<std::function<void(Ref*)>>fun;
	for (auto money = standing->getMoney(), num = 1; money; money /= 10, num *= 10)
	{
		txt.push_back(StringUtils::format("  存%d  ", num));
		fun.push_back([=](Ref* ref)
		{
			auto delta = std::min(num, standing->getMoney());
			standing->setMoney(standing->getMoney() - delta);
			standing->setDeposit(standing->getDeposit() + delta);
		});
	}
	for (auto money = standing->getDeposit(), num = 1; money; money /= 10, num *= 10)
	{
		txt.push_back(StringUtils::format("  取%d  ", num));
		fun.push_back([=](Ref* ref)
		{
			auto delta = std::min(num, standing->getDeposit());
			standing->setMoney(standing->getMoney() + delta);
			standing->setDeposit(standing->getDeposit() - delta);
		});
	}
	pop->setMenu(fun, txt);
	pop->setCallBack([=](Ref* ref)
	{
		auto pop1 = PopUpLayer::create();
		pop1->setTitle(name_);
		std::vector<std::string>txt1;
		std::vector<std::function<void(Ref*)>>fun1;
		if (!standing->getLoan())
		{
			txt1.push_back(StringUtils::format(" 贷款%d ", loan_value));
			fun1.push_back([=](Ref* ref)
			{
				standing->setMoney(standing->getMoney() + loan_value);
				standing->setLoan(loan_value);
				pop1->removeFromParentAndCleanup(true);
				SendMsg(msg_make_go_apper);
			});
		}
		else
		{
			txt1.push_back(StringUtils::format(" 还款%d ", loan_value));
			fun1.push_back([=](Ref* ref)
			{
				standing->setMoney(standing->getMoney() - loan_value);
				standing->setLoan(0);
				pop1->removeFromParentAndCleanup(true);
				SendMsg(msg_make_go_apper);
			});
		}
		pop1->setMenu(fun1, txt1);
		pop1->setCallBack([=](Ref* ref) {SendMsg(msg_make_go_apper); }, "取消");
		pop1->setPosition(Vec2::ZERO);
		map_scene->addChild(pop1, 51);
	});
	pop->setPosition(Vec2::ZERO);
	map_scene->addChild(pop, 50);
	return true;
}

bool Bank::byLand(Character* standing)
{
	auto game_controller = GetGameController();
	auto map_scene = GetMapScene();
	auto pop = PopUpLayer::create();
	pop->setTitle(name_);
	std::vector<std::string>txt;
	std::vector<std::function<void(Ref*)>>fun;
	for (auto money = standing->getMoney(),num=1; money; money /= 10,num*=10)
	{
		txt.push_back(StringUtils::format("  存%d  ", num));
		fun.push_back([=](Ref* ref)
		{
			auto delta = std::min(num, standing->getMoney());
			standing->setMoney(standing->getMoney() - delta);
			standing->setDeposit(standing->getDeposit() + delta);
		});
	}
	for (auto money = standing->getDeposit(), num = 1; money; money /= 10, num *= 10)
	{
		txt.push_back(StringUtils::format("  取%d  ", num));
		fun.push_back([=](Ref* ref)
		{
			auto delta = std::min(num, standing->getDeposit());
			standing->setMoney(standing->getMoney() + delta);
			standing->setDeposit(standing->getDeposit() - delta);
		});
	}
	pop->setMenu(fun, txt);
	pop->setCallBack([=](Ref* ref) {game_controller->moveOneStep(game_controller->judgeDirection(standing->getCurPos())); });
	pop->setPosition(Vec2::ZERO);
	map_scene->addChild(pop,50);
	return true;
}


