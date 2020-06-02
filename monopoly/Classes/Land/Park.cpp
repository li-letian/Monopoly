//#include "cocos2d.h"
//#include "Park.h"
//#include "Scene/MapScene.h"
//#include "Common/CommonMethod.h"
//#include "Common/CommonConstant.h"
//#include "Incident/PopUpLayer.h"
//
//
//USING_NS_CC;
//
//Business* Business::create(Business *target)
//{
//	auto pRet = new(std::nothrow) Park();
//	if (pRet && pRet->init())
//	{
//		auto tile_size = map_scene->getMap()->getTileSize();
//		pRet->setMapScene(map_scene);
//		pRet->name_ = std::string("商业用地") + StringUtils::format("%d", index);
//		pRet->setAnchorPoint(Vec2(0.5f, 0.5f));
//		auto back = 0;
//		for (int idx = index + 1; map_scene->getType(idx) == land_business || map_scene->getType(idx) == land_park || map_scene->getType(idx) == land_resort || map_scene->getType(idx) == land_mall || map_scene->getType(idx) == land_institute; idx++)
//		{
//			back++;
//		}
//		if (back % 2 == 1)
//		{
//			pRet->index_ = index;
//			pRet->index_larger_ = index + 1;
//			map_scene->getLand(index + 1) = pRet;
//		}
//		else
//		{
//			pRet->index_ = index - 1;
//			pRet->index_larger_ = index;
//			map_scene->getLand(index - 1) = pRet;
//		}
//		pRet->setPosition(map_scene->pos(pRet->index_));
//		map_scene->getMap()->addChild(pRet, 1);
//		pRet->autorelease();
//		return pRet;
//	}
//	else
//	{
//		delete pRet;
//		pRet = nullptr;
//		return nullptr;
//	}
//}
//
//bool Business::promote()
//{
//	if (building_) return building_->promote();
//	auto pop = PopUpLayer::create();
//	pop->setTitle("请选择");
//	std::vector<std::string>pic;
//	std::vector<ccMenuCallback>callback;
//	pic.push_back("park.png");
//	callback.push_back([=](Ref* ref) {
//
//
//	});
//	pic.push_back("resort.png");
//	callback.push_back([=](Ref* ref) {
//
//	});
//	pic.push_back("mall.png");
//	callback.push_back([=](Ref* ref) {
//
//	});
//	pic.push_back("institute.png");
//	callback.push_back([=](Ref* ref) {
//
//	});
//	pop->setMenu(pic, callback);
//	pop->setPosition(Vec2(0, 0));
//	map_scene_->addChild(pop, 51);
//	return true;
//
//	this->initWithFile(StringUtils::format("hotel%d.png", rank_));
//	setAnchorPoint(Vec2(0.5f, 0));
//	setPosition(map_scene_->pos(index_) + Vec2(0, map_scene_->getMap()->getTileSize().height));
//}
//
//bool Business::demote()
//{
//	if (building_) building_->demote();
//	building_ = nullptr;
//	type = land_business;
//	return false;
//}
//
//bool Business::onLand(Character* standing)
//{
//	auto pop = PopUpLayer::create();
//	pop->setTitle(name_);
//	if (!owner_)
//	{
//		auto text = std::string("看起来真是很有前景的一块地呢，确认以 ") + StringUtils::format("%d", sell_value_) + std::string("的价格购买这块土地吗？");
//		pop->setContent(text);
//		auto yes = [=](Ref* ref)
//		{
//			auto money = standing->getMoney();
//			if (money > sell_value_)
//			{
//				standing->setMoney(money - sell_value_);
//				owner_ = standing;
//				color_ = Sprite::create(StringUtils::format("character%d.png", standing->getTag()));
//				this->initWithFile(StringUtils::format("character%d.png", standing->getTag()));
//				this->setPosition(map_scene_->pos(index_));
//				this->setAnchorPoint(Vec2(0.5f, 0.5f));
//				color_->setPosition(map_scene_->pos(index_larger_));
//				color_->setAnchorPoint(Vec2(0.5f, 0.5f));
//				map_scene_->getMap()->addChild(color_, 1);
//				sendMsg(msg_make_go_apper);
//				//画点东西表示已经买完了
//			}
//			else
//			{
//				auto fail = PopUpLayer::create();
//				fail->setTitle("购买失败");
//				fail->setContent("钱都不够了咋还还剁手呢？快去整点钱吧");
//				fail->setCallBack([=](Ref* ref) {
//					sendMsg(msg_make_go_apper); });
//				fail->setPosition(Vec2(0, 0));
//				map_scene_->addChild(fail, 51);
//			}
//		};
//		auto no = [=](Ref* ref) { sendMsg(msg_make_go_apper); };
//		pop->setCallBack(yes, no);
//		pop->setPosition(Vec2(0, 0));
//		map_scene_->addChild(pop, 50);
//	}
//	else
//	{
//		if (standing->getTag() == owner_->getTag() && !building_)
//		{
//			auto text = std::string("看起来真是很有前景的一块地呢，确认要升级这块土地吗？");
//			pop->setContent(text);
//			auto yes = [=](Ref* ref)
//			{
//				promote();
//				sendMsg(msg_make_go_apper);
//			};
//			auto no = [=](Ref* ref) {sendMsg(msg_make_go_apper); };
//			pop->setCallBack(yes, no);
//			pop->setPosition(Vec2(0, 0));
//			map_scene_->addChild(pop, 50);
//		}
//		else
//		{
//			building_->onLand(standing);
//		}
//	}
//	return true;
//}