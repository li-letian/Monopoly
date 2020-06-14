#include "Incident/PopUpLayer.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Scene/MapScene.h"
#include "AudioEngine.h"
#include "Scene/GameController.h"

bool PopUpLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	//添加屏蔽层
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//添加背景
	auto visible_size = Director::getInstance()->getVisibleSize();
	back_ground_ = Sprite::create("dialog_bg.png");
	back_ground_->setAnchorPoint(Vec2(0.5f, 0.5f));
	back_ground_width_ = back_ground_->getContentSize().width;
	back_ground_height_ = back_ground_->getContentSize().height;
	back_ground_->setPosition(Vec2((visible_size.width - grid_distance * 16) / 2,
		visible_size.height *0.75f));
	this->addChild(back_ground_);

	return true;
}

void PopUpLayer::setTitle(const std::string& title)
{
	auto title_label = Label::createWithSystemFont(ZH(title), "华文琥珀", 30);
	title_label->setColor(Color3B(0, 0, 0));
	title_label->setAnchorPoint(Vec2(0.5f, 0.5f));
	title_label->setPosition(Vec2(back_ground_width_ / 2, back_ground_height_ - 2 * grid_distance));
	back_ground_->addChild(title_label);
}

void PopUpLayer::setMenu(const std::vector < std::string>pic, const std::vector<std::function<void(Ref* ref)>>callback)
{
	for (decltype(pic.size()) i = 0; i < pic.size(); i+=4)
	{
		auto menu = Menu::create();
		for (decltype(i) j = i; j < i + 4; j++)
		{
			if (j >= pic.size()) break;
			auto menu_item = MenuItemImage::create(pic.at(j), pic.at(j), [=](Ref* ref) { callback.at(j)(ref); this->removeFromParentAndCleanup(true); });
			menu->addChild(menu_item);
		}
		if (!menu->getChildrenCount()) break;
		menu->alignItemsHorizontally();
		menu->setAnchorPoint(Vec2(0.5f, 0.5f));
		menu->setPosition(Vec2(back_ground_width_ / 2, back_ground_height_ - (7+i) * grid_distance));
		back_ground_->addChild(menu);
	}
}


void PopUpLayer::setMenu(const std::vector<std::function<void(Ref* ref)>>callback, const std::vector<std::string>txt)
{
	MenuItemFont::setFontName("华文琥珀");
	MenuItemFont::setFontSize(30);
	for (decltype(txt.size()) i = 0; i < txt.size(); i += 4)
	{
		auto menu = Menu::create();
		for (decltype(i) j = i; j < i + 4; j++)
		{
			if (j >= txt.size()) break;
			auto menu_item = MenuItemFont::create(ZH(txt.at(j)), [=](Ref* ref) { callback.at(j)(ref); });
			menu->setColor(Color3B(0, 0, 0));
			menu->addChild(menu_item);
		}
		if (!menu->getChildrenCount()) break;
		menu->alignItemsHorizontally();
		menu->setAnchorPoint(Vec2(0.5f, 0.5f));
		menu->setPosition(Vec2(back_ground_width_ / 2.0f, back_ground_height_ - (7.0f + i*0.6f) * grid_distance));
		back_ground_->addChild(menu);
	}
}

void PopUpLayer::setContent(const std::string& content)
{
	auto content_label = Label::createWithSystemFont(ZH(content), "华文琥珀", 20);
	content_label->setColor(Color3B(0, 0, 0));
	content_label->setDimensions(back_ground_width_ - 4 * grid_distance, back_ground_height_ - 10 * grid_distance);
	content_label->setAnchorPoint(Vec2(0.5f, 0.5f));
	content_label->setPosition(Vec2(back_ground_width_ / 2, back_ground_height_ / 2));
	back_ground_->addChild(content_label);
}

void PopUpLayer::setCallBack(std::function<void(Ref * render)> confirm_call_back,const std::string text)
{
	if (GetGameController()->getCurCharacter()->getIsAI())
	{
		call_back_func_ = [=]() {
			confirm_call_back(nullptr);
			this->removeFromParent();
		};
	}
	else
	{
		auto soundEffectID = AudioEngine::play2d("bottom_down.mp3", false);
		MenuItemFont::setFontName("华文琥珀");
		MenuItemFont::setFontSize(25);
		auto confirm_item = MenuItemFont::create(ZH(text), [=](Ref* ref) {
			confirm_call_back(ref);
			this->removeFromParentAndCleanup(true); });
		confirm_item->setColor(Color3B(0, 0, 0));
		confirm_item->setAnchorPoint(Vec2(0.5f, 0));
		confirm_item->setPosition(Vec2(back_ground_width_ / 2, 2 * grid_distance));
		auto menu = Menu::create(confirm_item, nullptr);
		menu->setAnchorPoint(Vec2(0, 0));
		menu->setPosition(Vec2(0, 0));
		back_ground_->addChild(menu);
	}
}

void PopUpLayer::setCallBack(std::function<void(Ref * render)> confirm_call_back, std::function<void(Ref * render)> cancel_call_back)
{
	auto soundEffectID = AudioEngine::play2d("bottom_down.mp3", false);
	MenuItemFont::setFontName("华文琥珀");
	MenuItemFont::setFontSize(25);

	auto confirm_item = MenuItemFont::create(ZH("确认"), [=](Ref* ref) {
		auto soundEffectID = AudioEngine::play2d("bottom_up.mp3", false);
		confirm_call_back(ref);
		this->removeFromParentAndCleanup(true); });
	confirm_item->setColor(Color3B(0, 0, 0));
	confirm_item->setAnchorPoint(Vec2(0, 0));
	confirm_item->setPosition(Vec2(2 * grid_distance, 2 * grid_distance));

	auto cancel_item = MenuItemFont::create(ZH("取消"), [=](Ref* ref) {
		auto soundEffectID = AudioEngine::play2d("bottom_up.mp3", false);
		cancel_call_back(ref);
		this->removeFromParentAndCleanup(true);
	});
	cancel_item->setColor(Color3B(0, 0, 0));
	cancel_item->setAnchorPoint(Vec2(1.0f, 0));
	cancel_item->setPosition(Vec2(back_ground_width_ - 2 * grid_distance, 2 * grid_distance));

	auto menu = Menu::create(confirm_item, cancel_item, nullptr);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(0,0));
	back_ground_->addChild(menu);
}

void PopUpLayer::setOnScene(int z_order)
{
	auto map_scene = GetMapScene();
	this->setPosition(Vec2::ZERO);
	map_scene->addChild(this, z_order);
	if (GetGameController()->getCurCharacter()->getIsAI())
	{
		auto sequence = Sequence::create(DelayTime::create(1.5f), CallFunc::create(call_back_func_), nullptr);
		GetGameController()->runAction(sequence);
	}
}
